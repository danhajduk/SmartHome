/**************************************************************************************
	tSet.h - Library for seting up timer or time
	Created by Dan Hajduk on April 1, 2017

	Last Modified April 1, 2017

/*************************************************************************************/ 


#ifndef tSet_H_
#define tSet_H_
class tSet
{
	public:

	tSet();
	bool isSet ;
	void tick();
	String showTime();
	bool touch();
	void clearTime();
	bool timeCheck(int HH,int MM);
	void timeSet(int HH, int MM);

	private:
	int _HH = 0;
	int _MM = 0;
	int _SS = 0;
	int _MS = 0;
	
};





#endif /* tSet_H_ */