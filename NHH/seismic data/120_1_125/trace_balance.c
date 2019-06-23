/*************************************************************************
 > File Name: trace_balance.c
 > Author: sean
 > Mail: seancug@cug.edu.cn
 > Created Time: Mon 30 Jul 2018 10:56:28 AM CST
 >trace balance
 ************************************************************************/

#include <rsf.h>
int main(int argc, char* argv[]) {

	int nt, nx, n3,i3, it, ix;
	float *ctrace;
	sf_file in, out;

	sf_init(argc, argv);
	in = sf_input("in");
	out = sf_output("out");

	//if (SF_COMPLEX != sf_gettype(in))
	//	sf_error("Need complex input");

	
	if (!sf_histint(in, "n1", &nt))
		sf_error("No n1=");
	if (!sf_histint(in, "n2", &nx))
		sf_error("No n2=");

	
	n3 = sf_leftsize(in, 2);

	ctrace = sf_floatalloc(nt);
	int m,pb;
	if (!sf_getint("mbal", &m))
		m = 0;

	if (!sf_getint("pbal", &pb))
	
		pb = 0;
	sf_warning("begin trace balance mbal=%d,  pbal=%d", m, pb);

	/* Loop over shots */
	for (i3 = 0; i3 < n3; i3++) {
		/* Loop over trace*/
		for (ix = 0; ix < nx; ix++) {
			sf_floatread(ctrace, nt, in);

			/* Loop over time */
			if (m) {
				float mean = 0.0;
				for (it = 0; it < nt; it++) {
					mean += ctrace[it];
				}
				mean /= nt;

			//	 sf_warning("\r mean amps%f  %d", mean,ix+1);
				if (mean) {
					for (it = 0; it < nt; it++) {
						ctrace[it] -= mean;
					}
				}
				sf_floatwrite(ctrace, nt, out);
			}

			if (pb) {
				float val;
				float rmsq = 0.0;
				for (it = 0; it < nt; it++) {
					val = ctrace[it];
					rmsq += val * val;
				}
				rmsq = sqrt(rmsq / nt);
				//ssf_warning("\r%f  %d", rmsq,ix+1);
				
				if (rmsq) {
					for (it = 0; it < nt; it++) {
						ctrace[it] /= rmsq;
					}
				}
				sf_floatwrite(ctrace, nt, out);
			}	
		}
	}
	sf_warning("Finish trace balance");
	exit(0);
}
