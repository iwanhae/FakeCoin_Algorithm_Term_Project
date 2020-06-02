#include "common.h"

knownSet CompareBy3(vector<int> real, vector<int> fake, vector<int> unknown) {
	// If we use p directly, parameter flag can be added to determine comparison should be r2f1 or r1f2
	int left[4];
	int right[4];
	bool completed = true;
	knownSet output;
	right[0] = fake[0];
	right[1] = real[0];
	right[2] = real[1];
	right[3] = -1;
	left[0] = unknown[0];
	left[1] = unknown[1];
	left[2] = unknown[2];
	left[3] = -1;
	switch (balance(left, right)) {
	case LARGE: {
		// All real
		for (int i = 0; i < 3; i++) {
			real.push_back(unknown[i]);
		}
		break;
	}
	case EQUAL: {
		// 2 real coins and 1 fake coin
		left[0] = unknown[0];
		left[1] = -1;
		right[0] = unknown[1];
		right[1] = -1;
		switch (balance(left, right)) {
		case LARGE: {
			// 0>1, ==> 0,2 real, 1 fake
			real.push_back(unknown[0]);
			fake.push_back(unknown[1]);
			real.push_back(unknown[2]);
			break;
		}
		case EQUAL: {
			// 0==1 ==> 0,1 real, 2 fake
			real.push_back(unknown[0]);
			real.push_back(unknown[1]);
			fake.push_back(unknown[2]);
			break;
		}
		case SMALL: {
			// 0<1 ==> 1,2 real, 0 fake
			fake.push_back(unknown[0]);
			real.push_back(unknown[1]);
			real.push_back(unknown[2]);
			break;
		}
		}
		break;
	}
	case SMALL: {
		// 1 or 0 real coin and 2 or 3 fake coins
		left[0] = unknown[0];
		left[1] = -1;
		right[0] = unknown[1];
		right[1] = -1;
		switch (balance(left, right)) {
		case LARGE: {
			// 0>1 ==> 0 real, 1,2 fake
			real.push_back(unknown[0]);
			fake.push_back(unknown[1]);
			fake.push_back(unknown[2]);
			break;
		}
		case EQUAL: {
			// 0==1 ==> 0,1 fake, 2 unknown
			fake.push_back(unknown[0]);
			fake.push_back(unknown[1]);
			completed = false;
			break;
		}
		case SMALL: {
			// 0<1 ==> 1 real, 0,2 fake
			fake.push_back(unknown[0]);
			real.push_back(unknown[1]);
			fake.push_back(unknown[2]);
			break;
		}
		}
		break;
	}
	}

	if (completed) {
		for (int i = 0; i < 3; i++) {
			unknown.erase(unknown.begin());
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			unknown.erase(unknown.begin());
		}
	}
	output.real = real;
	output.fake = fake;
	output.unknown = unknown;

	return output;
}