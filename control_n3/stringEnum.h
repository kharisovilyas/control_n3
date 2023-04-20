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
            return "\n����� � ����� ������ �� ����������!\n";

        case StringEnum::negative_size:
            return "���� �������� ��������������� ���������� ����� ��� ��������\n��������� ����\n";

        case StringEnum::invalid_columns:
            return "���������� �������� ������ ��� �� ������� !\n��������� ����\n";

        case StringEnum::invalid_rows:
            return "���������� ����� ������ ��� �� ������� !\n��������� ����\n";

        case StringEnum::null_column:
            return "������ ������ �������! \n��������� ����\n";

        case StringEnum::null_row:
            return "������� ������ ������ !\n��������� ����\n";

        case StringEnum::correct:
            return "\n������ ������� ��������!\n";

        default:
            return "\n��� �� ����� �� ���!\n";
        }
    }

private:
    StringEnum m_e;
};
