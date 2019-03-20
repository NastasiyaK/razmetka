#include "stdafx.h"
#include "leads.h"
#include "one lead.h"


void one_lead::initialization(leads_name type) {

	
	if (type == II || type == I || type == III || type == aVR || type == aVL || type == aVF)
	{
		QRS_height = 2.2f; //max amplitude of QRS complex 
		ampl_P_standart = 0.25f;
		ampl_T_standart = 0.6f;
		ampl_P_threshold = 0.05f;
		QRS_hight_min = 0.25f;
		QRS_filtered_min = 0.2f;
		ampl_P_threshold = 0.1;

	}


	if ( type == aVR || type == v2)
	{
		main_peak_in_interval = 'S';
	}else
	{
		main_peak_in_interval = 'R';
	}


	if (type == v1 || type == v2 || type == v3 || type == v4 || type == v6)
	{
		QRS_height = 2.5f; //max amplitude of QRS complex 
		ampl_P_standart = 0.25f;
		ampl_T_standart = 1.5f;
		ampl_P_threshold = 0.05f;
		QRS_hight_min = 0.3f;
		QRS_filtered_min = 0.25f;
		ampl_P_threshold - 0.1;
	}

	if (type == v1 || type == v2 )
	{
		QRS_height = 2.5f; //max amplitude of QRS complex
		ampl_P_standart = 0.25f;
		ampl_T_standart = 1.5f;
		ampl_P_threshold = 0.05f;
		QRS_hight_min = 0.3f;
		QRS_filtered_min = 0.1f;
	}
	if (type == v5) 
	{
		QRS_height = 2.22f;//max amplitude of QRS complex 
		
		ampl_P_standart = .25f;
		ampl_T_standart = 1.5f;
		ampl_P_threshold = .005f;
		QRS_hight_min = 0.2f;
	}
	average_amplitude.set_start_value(QRS_filtered_min);
	

}