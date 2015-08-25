#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <Qstring>
#include <QFileDialog>

namespace Utils {
    template<typename T>
    T abs(const T& val) {
        return val > 0 ? val : val * -1;
    }

    std::wstring GetSaveFileNameFromDialog();
    std::wstring GetOpenFileNameFromDialog();
}
#endif // UTILS_H
