#include <iostream>
#include "tests/TestHashTable.hpp"
#include "containers/HashTable.h"
#include "containers/Histogram.h"
#include "tests/TestHistogram.h"
#include "utility/GUI.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HistogramApp window;
    window.show();

    return app.exec();
}

