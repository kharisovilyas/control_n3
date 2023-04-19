#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "matrix.h"

namespace ui {

	class loopedMenu {

	};

	class correctness {
	public:
		int getInt();
		int getMenuVar(int, int);
		double getDouble();
		bool getBool();
		int getIntField();
		double getDoubleField();
	};

	class inOutConsole {
	public:
		void readConsole(unique_ptr<Matrix>&);
		void outConsole(unique_ptr<Matrix>&, map<string, pair<int, int>>&) const;
		void outConsole(unique_ptr<Matrix>&) const;
	};

	class fileReader {
	public:
		void readFile(unique_ptr<Matrix>&, string);
		void fillFile(unique_ptr<Matrix>&, map<string, pair<int, int>>&) const;
		void fillFile(unique_ptr<Matrix>&) const;
		void implFile(unique_ptr<Matrix>&, string);
	};

	class fillingRandom {
	public:
		void filling(unique_ptr<Matrix>&);
	};
}