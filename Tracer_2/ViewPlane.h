#ifndef __VIEWPLANE__
#define __VIEWPLANE__

class ViewPlane {
public:
	int hres;
	int vres;
	float s;
	int num_samples;
	float gamma;
	float inv_gamma;
	//bool show_out_of_gamut;

	ViewPlane();
	ViewPlane(const ViewPlane& vp);
	ViewPlane& operator= (const ViewPlane& rhs);
	~ViewPlane();

	void set_hres(const int h_res);
	void set_vres(const int v_res);
	void set_pixel_size(const float size);
	void set_gamma(const float g);
	//void set_gamut_display(const bool show);
	void set_samples(const int n);
};

// set_hres
inline void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}


// set_vres

inline void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}


// set_pixel_size

inline void ViewPlane::set_pixel_size(const float size) {
	s = size;
}


// ------------------------------------------------------------------------------ set_gamma


inline void ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = float(1.0 / gamma);
}


// ------------------------------------------------------------------------------ set_gamut_display
/*
inline void ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}
*/

// ------------------------------------------------------------------------------ set_samples
inline void ViewPlane::set_samples(const int n) {
	num_samples = n;
}

#endif // __VIEWPLANE__