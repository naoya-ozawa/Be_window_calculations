#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double Be_density(){
	// Based on Material Certification from Materion
	// Batch Number 2218368
	// Delivery Number 81126670
	double r_Be = 0.999;
	double r_BeO = 0.00060; // UL
	double r_Al = 0.0001;
	double r_Ca = 0.0002; // UL
	double r_C = 0.0003;
	double r_Cr = 0.000030;
	double r_Co = 0.000005; // UL
	double r_Cu = 0.000020;
	double r_Fe = 0.000300;
	double r_Pb = 0.000005; // UL
	double r_Mg = 0.000060; // UL
	double r_Mn = 0.000030; // UL
	double r_Mo = 0.000010; // UL
	double r_Ni = 0.000100;
	double r_Si = 0.000100; // UL
	double r_Ag = 0.000005; // UL
	double r_Ti = 0.000010;
	double r_Zn = 0.000100; // UL

	double sum = r_Be + r_BeO + r_Al + r_Ca + r_C + r_Cr + r_Co + r_Cu + r_Fe + r_Pb + r_Mg + r_Mn + r_Mo + r_Ni + r_Si + r_Ag + r_Ti + r_Zn;
	// Densities (g/cm^3) at room temperature from Wikipedia
	double rho_Be = 1.85;
	double rho_BeO = 3.02;
	double rho_Al = 2.70;
	double rho_Ca = 1.550;
	double rho_C = 1.8;
	double rho_Cr = 7.19;
	double rho_Co = 8.90;
	double rho_Cu = 8.94;
	double rho_Fe = 7.874;
	double rho_Pb = 11.34;
	double rho_Mg = 1.738;
	double rho_Mn = 7.21;
	double rho_Mo = 10.28;
	double rho_Ni = 8.908;
	double rho_Si = 2.3290;
	double rho_Ag = 10.49;
	double rho_Ti = 4.506;
	double rho_Zn = 7.14;

	double density = r_Be*rho_Be + r_BeO*rho_BeO + r_Al*rho_Al + r_Ca*rho_Ca + r_C*rho_C + r_Cr*rho_Cr + r_Co*rho_Co + r_Cu*rho_Cu + r_Fe*rho_Fe + r_Pb*rho_Pb + r_Mg*rho_Mg + r_Mn*rho_Mn + r_Mo*rho_Mo + r_Ni*rho_Ni + r_Si*rho_Si + r_Ag*rho_Ag + r_Ti*rho_Ti + r_Zn*rho_Zn;

	return density/sum;
}


int main(int argc, char** argv){

	double product_t;
	printf("The nominal thickness of the Be (um): ");
	scanf("%lf",&product_t);

	double product_d;
	printf("The nominal diameter of the Be (mm): ");
	scanf("%lf",&product_d);

	double thickness_nom, thickness_tol, diameter_nom, diameter_tol;

	if (product_t == 10.0){
		thickness_nom = 10.;
		thickness_tol = 0.005; // +5 um / -0 um
		printf("Nominal thickness: %.3f +%.3f/-0 um\n",thickness_nom,thickness_tol);
	}else if (product_t == 8.0){
		thickness_nom = 8.;
		thickness_tol = 0.005; // +5 um / -0 um
		printf("Nominal thickness: %.3f +%.3f/-0 um\n",thickness_nom,thickness_tol);
	}else{
		printf("I do not have the data for that!\n");
		exit(0);
	}

	if (product_d == 17.0){
		diameter_nom = 17.;
		diameter_tol = 0.08; // +-0.08 mm
		printf("Nominal diameter: %.2f +-%.2f mm\n",diameter_nom,diameter_tol);
	}else{
		printf("I do not have the data for that!\n");
		exit(0);
	}

	double measured_d;
	printf("The measured diameter of the Be (mm): ");
	scanf("%lf",&measured_d);

	double measured_rad_cm = 0.5 * measured_d / 10.0; // measured radius of Be in cm

	double measured_w;
	printf("The measured weight of the Be (mg): ");
	scanf("%lf", &measured_w);

	double measured_w_g = measured_w * 1000.0; // measured weight of Be in g

	double d_Be = Be_density();
	printf("The density of the Be: %.2f g/cm3\n",d_Be);

	double measured_t_cm = measured_w_g / (M_PI*measured_rad_cm*measured_rad_cm*d_Be); // "measured" thickness in cm

	double measured_t = measured_t_cm / 10000.0; // "measured" thickeness in um

	printf("Thickness: %3.2f um\n",measured_t);

	return 0;
}
