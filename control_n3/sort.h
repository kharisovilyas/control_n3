#pragma once
#include "ISort.h"
#include "Matrix.h"


namespace sort {

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
		void Sort(unique_ptr<Matrix>& );
		int Partition(unique_ptr<Matrix>&, int, int, int);
		void QuickSortRecursive(unique_ptr<Matrix>&, int, int, int);

	};
}
