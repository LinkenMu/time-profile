#include "timeprofile.h"
#include <algorithm>
#include <fstream>
#include <iostream>

//#define TO_FILE

using namespace std;

ProfileTimer::ProfileTimer()
{
	file_ = nullptr;
}

ProfileTimer::ProfileTimer(const char* file)
{
	file_ = file;
}


void ProfileTimer::Start(const char *name)
{
	
	auto result = profiles_.find(name);
	if(result == profiles_.end()) // new one
	{
		ProfileInfo new_profile;
		new_profile.times = 0;
		new_profile.totalTime = 0;
		new_profile.maxTime = LLONG_MIN;
		new_profile.minTime = LLONG_MAX;
		new_profile.now = chrono::system_clock::now();
		profiles_.emplace(name, new_profile);
	}
	else
	{
		ProfileInfo *used = &result->second;
		used->now = chrono::system_clock::now();
	}
}

void ProfileTimer::Stop(const char *name)
{

	auto result = profiles_.find(name);
	if (result == profiles_.end()) // discard
	{

	}
	else
	{
		ProfileInfo *used = &result->second;
		long long time_count = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - used->now).count();
		used->maxTime = max(used->maxTime, time_count);
		used->minTime = min(used->minTime, time_count);
		used->totalTime += time_count;
		used->times++;

	}
}
void ProfileTimer::Reset(const char *name)
{
	auto tmp = profiles_.find(name);
	if (tmp != profiles_.end())
		profiles_.erase(name);

}


void ProfileTimer::Report()
{
	ofstream record_file;
	if (file_ != nullptr)
		record_file.open(file_, ios_base::out | ios_base::app);

	int i = 0;
	for (auto &iter : profiles_)
	{
		string name = iter.first;
		ProfileInfo &item = iter.second;
		char tmp[512] = { 0 };
		if (item.times > 0)
		{
			snprintf((char*)&tmp,512,"[%d] %s : times = %lld, totaltime = %lld us, average = %lld us , min = %lld us ,max = %lld us\n", i, name.data(), item.times, item.totalTime, item.totalTime / item.times, item.minTime, item.maxTime);
			if (record_file.is_open())
			{
				record_file.write((char*)&tmp, strlen(tmp));
			}
			else
			{
				cout << tmp << endl;
			}

			i++;
		}
	}
	if (record_file.is_open())
		record_file.close();

}


void ProfileTimer::Clear()
{
	if (!profiles_.empty())
		profiles_.clear();
}
