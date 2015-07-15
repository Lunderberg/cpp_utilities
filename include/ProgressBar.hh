#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

class ProgressBar {
public:
	ProgressBar(int total,int skip);
	~ProgressBar();
	void Show(int current);
private:
	int total;
	int update_every;
	int iter_since_update;
	double time_start;
};

#endif

