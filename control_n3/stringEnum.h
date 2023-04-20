#include <string>

enum class StringEnum {
    nonexist = 0,
    negative_size = 1,
    invalid_columns = 2,
    invalid_rows = 3,
    null_column = 4,
    null_row = 5,
    correct = 6
};

class StringEnumHelper {
public:

    StringEnumHelper(StringEnum e) : m_e(e) {}

    string toString(StringEnumHelper val) {
        return static_cast<string> (val);
    }

    bool operator==(const StringEnumHelper& other) const {
        return m_e == other.m_e;
    }

    bool operator!=(const StringEnumHelper& other) const {
        return m_e != other.m_e;
    }

    operator std::string() const {
        switch (m_e) {
        case StringEnum::nonexist:
            return "\nФайла с таким именем не существует!\n";

        case StringEnum::negative_size:
            return "Файл содержит неположительные количество строк или столбцов\nИсправьте файл\n";

        case StringEnum::invalid_columns:
            return "Количество столбцов больше чем вы указали !\nИсправьте файл\n";

        case StringEnum::invalid_rows:
            return "Количество строк больше чем вы указали !\nИсправьте файл\n";

        case StringEnum::null_column:
            return "Найден пустой столбец! \nИсправьте файл\n";

        case StringEnum::null_row:
            return "Найдена пустая строка !\nИсправьте файл\n";

        case StringEnum::correct:
            return "\nДанные успешно записаны!\n";

        default:
            return "\nЧто то пошло не так!\n";
        }
    }

private:
    StringEnum m_e;
};
