#include <iostream>

class Date {
    int year_;
    int month_; // 1부터 12까지.
    int day_; // 1부터 31까지.

    public:
        void SetDate(int year, int month, int date) {
			year_ = year;
			month_ = month;
			day_ = date;
		}
        void AddDay(int inc) {
			int days;
			switch (month_) {
				case 2:
					if (!(year_ % 4) && ((year_ % 100) || !(year_ % 400))) // leap year
						days = 29;
					else
						days = 28;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					days = 30;
					break;
				default:
					days = 31;
					break;
			}
			if (day_ + inc > days) {
				AddMonth(1);
				AddDay(inc - days);
			} else {
				day_ += inc;
			}
		}

        void AddMonth(int inc) {
			AddYear((month_ + inc) / 12);
			month_ = (month_ + inc) % 12;
		}

        void AddYear(int inc) {
			year_ += inc;
		}

        void ShowDate() {
			std::cout << year_ << "/" << month_ << "/" << day_ << std::endl;
		}
};

int main() {
	// 예외 처리는 하지 않았음.
	Date date;
	date.SetDate(2012, 2, 28);
	date.AddDay(3);
	date.ShowDate();
}
