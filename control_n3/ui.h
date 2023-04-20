#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "matrix.h"
#include "stringEnum.h"

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
		StringEnumHelper readConsole(unique_ptr<Matrix>&);
		void outConsole(unique_ptr<Matrix>&, map<string, pair<int, int>>&) const;
		void outConsole(unique_ptr<Matrix>&) const;
	};

	class fileReader {
	public:
		StringEnumHelper readFile(unique_ptr<Matrix>&, string);
		StringEnumHelper implFile(unique_ptr<Matrix>&, string);
		void implFile(unique_ptr<Matrix>& matrix, string name, unique_ptr<Matrix>& sortMatrix);
		void implFillFile(unique_ptr<Matrix>&, unique_ptr<Matrix>&, map<string, pair<int, int>>&) const;
		void implFillFile(unique_ptr<Matrix>&) const;
		void outInitialDataInFile(unique_ptr<Matrix>& ) const;
	};

	class fillingRandom {
	public:
		StringEnumHelper filling(unique_ptr<Matrix>&);
	};
}