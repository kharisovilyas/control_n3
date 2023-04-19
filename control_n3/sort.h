#pragma once
#include "ISort.h"
#include <map>
#include "Matrix.h"


namespace sort {

	class controlSort {
	public:
		void startSort(unique_ptr<Matrix>&, unique_ptr<Matrix>&, map<string, pair<int, int>>&);
	};

	class bubbleSelection : public ISort {
	public:
		void Sort(unique_ptr<Matrix>&) override;
	};

	class insertion : public ISort {
	public:
		void Sort(unique_ptr<Matrix>& array);
	};

	class shell : public ISort {
	public:
		void Sort(unique_ptr<Matrix>& array);
	};

	class quickSort : public ISort {
	public:
		void Sort(unique_ptr<Matrix>&);
	};
}
