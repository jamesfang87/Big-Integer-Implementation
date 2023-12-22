#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;


class BigInt {
private:
    string digits;
    int sign;

public:
    explicit BigInt(string d) {
        if (d[0] == '-') {
            sign = -1;
            digits = d.substr(1, string::npos);
        } else {
            sign = 1;
            digits = d;
        }

        reverse(digits.begin(), digits.end());
    }

    pair<string, string> setup(const BigInt& n2) {
        string a = this->digits, b = n2.digits;

        if (b.size() > a.size()) {
            a.append(b.size() - a.size(), '0');
        } else if (b.size() < a.size()) {
            b.append(a.size() - b.size(), '0');
        }

        return make_pair(a, b);
    }

    bool larger(BigInt other) {
        if (this->digits.size() > other.digits.size()) {
            return true;
        } else if (this->digits.size() < other.digits.size()) {
            return false;
        } else {
            for (int i = digits.size() - 1; i >= 0; i--) {
                if (this->digits[i] > other.digits[i]) {
                    return true;
                }
            }
        }
        return false;
    }

    static BigInt add(string a, string b) {
        BigInt result = BigInt("");

        int carry = 0;
        for (int i = 0; i < b.size(); i++) {
            int digit1 = int(a[i]) - 48, digit2 = int(b[i]) - 48;

            result.digits += char(48 + (carry + digit1 + digit2) % 10);
            carry = (carry + digit1 + digit2) / 10;
        }

        if (carry != 0) {
            result.digits += char(48 + carry);
        }
        return result;
    }

    static BigInt sub(string a, string b) {
        BigInt result = BigInt("");

        // a - b
        for (int i = 0; i < b.size(); i++) {
            int digit1 = int(a[i]) - 48, digit2 = int(b[i]) - 48;

            if (digit1 < digit2) {
                result.digits += char(10 + digit1 - digit2 + 48);
                a[i + 1]--;
            } else {
                result.digits += char(digit1 - digit2 + 48);
            }
        }

        return result;
    }

    BigInt operator+ (const BigInt& other) {
        pair<string, string> nums = setup(other);
        BigInt ans = BigInt("");

        if (sign == other.sign) {
            ans = add(nums.first, nums.second);

            if (!sign) {
                ans.sign = -1;
            }
        } else {
            // find difference (larger number - smaller number)
            if (larger(other)) {
                ans = sub(nums.first, nums.second);

                // if negative number > positive number, change sign to negative
                if (!this->sign)
                    ans.sign = -1;
            } else {
                ans = sub(nums.second, nums.first);

                // if negative number > positive number, change sign to negative
                if (!other.sign)
                    ans.sign = -1;
            }
        }

        return ans;
    };

    BigInt operator-(BigInt other) {
        pair<string, string> nums = setup(other);
        BigInt ans = BigInt("");

        if (other.sign == 1) {
            other.sign = -1;
        } else {
            other.sign = 1;
        }

        if (sign == other.sign) {
            ans = add(nums.first, nums.second);

            if (sign == -1) {
                ans.sign = -1;
            }
        } else {
            // find difference (larger number - smaller number)
            if (larger(other)) {
                ans = sub(nums.first, nums.second);

                // if negative number > positive number, change sign to negative
                if (this->sign == -1)
                    ans.sign = -1;
            } else {
                ans = sub(nums.second, nums.first);

                // if negative number > positive number, change sign to negative
                if (other.sign == -1)
                    ans.sign = -1;
            }
        }


        return ans;
    }

    string ret_string() {
        string temp;
        for (int i = digits.size() - 1; i >= 0; i--) {
            temp += digits[i];
        }

        if (!this->sign)
            temp = '-' + temp;

        return temp;
    }
};


int main() {
    BigInt a = BigInt("9");
    BigInt b = BigInt("38");

    BigInt temp = a - b;
    std::cout << temp.ret_string();
}