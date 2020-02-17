#pragma once
#include <string>
#include <map>
#include <vector>
#include <chrono>

using namespace std;

class ProfileTimer {
public:
	ProfileTimer();
	ProfileTimer(const char* file);
	void Start(const char *name);
	void Stop(const char *name);
	void Reset(const char *name);
	void Report();
	void Clear();
	void Record(long long times, int start_wheel, int end_wheel);

private:

	const char* file_;

	struct ProfileInfo {
		long long times;//ͳ�ƴ�ʱ
		long long totalTime;//�ܹ���ʱ
		long long minTime;//��С������ʱ
		long long maxTime;//��󵥴���ʱ
		chrono::system_clock::time_point now;
	};

	typedef std::map<std::string, ProfileInfo> Profiles;

	Profiles    profiles_;

};
