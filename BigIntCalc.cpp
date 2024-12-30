#include <bits/stdc++.h>
using namespace std;

class calculator{
    vector<int> nums;

    public:
    calculator(){}

    calculator(string s){
        for(char ch: s){
            nums.push_back(ch-'0');
        }
    }

    calculator (int x){
        while(x){
            nums.push_back(x % 10);
            x /= 10;
        }
        reverse(nums.begin(),nums.end());
    }

    int size() const{
        return nums.size();
    }

    friend ostream& operator<<(ostream& os, const calculator& obj) {
        if (obj.size() == 0) {
            os << 0;
            return os;
        } else {
            for (int i : obj.nums)
                os << i;
        }
        return os;
    }

    friend istream& operator>>(istream& is, calculator& obj) {
        string input;
        is >> input;
        obj.nums.clear();

        for (char ch : input) {
            if (isdigit(ch)) {
                obj.nums.push_back(ch - '0');
            } else {
                cerr << "Invalid input: Non-numeric character encountered." << endl;
                obj.nums.clear();  // Clear the vector in case of invalid input
                break;
            }
        }

        return is;
    }

    bool operator<(const calculator& other) const{
        if(nums.size() < other.nums.size()){
            return true;
        }
        else if(nums.size() > other.nums.size()){
            return false;
        }
        else{
            for(int i = 0; i < nums.size(); i--){
                if(nums[i] < other.nums[i]){
                    return true;
                }
                else if(nums[i] > other.nums[i]){
                    return false;
                }
            }
            return false;
        }
        return false;
    }

    bool operator>=(const calculator& other) const{
        if(nums.size() > other.nums.size()){
            return true;
        }
        else if(nums.size() < other.nums.size()){
            return false;
        }
        else{
            for(int i = 0; i < nums.size(); i--){
                if(nums[i] > other.nums[i]){
                    return true;
                }
                else if(nums[i] < other.nums[i]){
                    return false;
                }
            }
            return true;
        }
        return true;
    }

    calculator operator+(const calculator& other) const{
        const vector<int>& a = nums;
        const vector<int>& b = other.nums;

        int m = a.size();
        int n = b.size();
        int carry = 0;

        int size = max(m,n);
        vector<int> result(size,0);
        
        for(int i = 0; i < size; i++){
            int x = (i < m) ? a[m-i-1] : 0;
            int y = (i < n) ? b[n-i-1] : 0;

            int sum = x + y + carry;
            result[size-i-1] = sum % 10;
            carry = sum / 10;
        }
        if(carry != 0){
            result.insert(result.begin(),carry);                        
        }

        calculator sum;
        sum.nums = result;
        return sum;
    }

    calculator operator-(const calculator& other) const{
        if (*this < other) {
            throw invalid_argument("Subtraction error: First BigInteger is less than the second.");
        }

        int i = nums.size() - 1;
        int j = other.nums.size() - 1;
        int borrow = 0;
        calculator result;

        while(i >= 0){
            int diff = nums[i] - borrow;
            if(j >= 0){
                diff -= other.nums[j];
                j--;
            }

            if (diff < 0){
                diff += 10;
                borrow = 1;
            }

            result.nums.insert(result.nums.begin(),diff);
            i--;
        }
        while(!result.nums.empty() && result.nums.front() == 0){
            result.nums.erase(result.nums.begin());
        }
        return result;
    }

    calculator operator*(const calculator& other) const{
        int m = nums.size();
        int n = other.nums.size();
        vector<int> result(n+m,0);
        
        for(int i = m - 1; i >= 0 ; i--){
            int carry = 0;
            for(int j = n - 1; j >= 0; j--){
                int product = (nums[i] * nums[j]) + result[i+j+1] + carry;
                result[i+j+1] = product % 10;
                carry = product / 10;
            }
            result[i] += carry;            
        }
        while(!result.empty() && result[0] == 0){
            result.erase(result.begin());
        }
        calculator multiplied;
        multiplied.nums = result;
        return multiplied;
    }

    calculator operator/(const calculator& divisor) const {
    if (divisor.nums.empty() || (divisor.nums.size() == 1 && divisor.nums[0] == 0)) {
        throw invalid_argument("Division by zero is not allowed.");
    }

    calculator quotient, remainder;
    remainder.nums.clear();

    for (int i = 0; i < nums.size(); ++i) {
        remainder.nums.push_back(nums[i]);
        
        while (!remainder.nums.empty() && remainder.nums[0] == 0) {
            remainder.nums.erase(remainder.nums.begin());
        }

        int q = 0;
        while (remainder >= divisor) {
            remainder = remainder - divisor;
            ++q;
        }
        quotient.nums.push_back(q);
    }
        
    while (!quotient.nums.empty() && quotient.nums[0] == 0) {
        quotient.nums.erase(quotient.nums.begin());
    }

    if (quotient.nums.empty()) {
        quotient.nums.push_back(0);
    }

    return quotient;
}


};

int main(){

    calculator x,y;
    cout<<"ENTER NUMBERS"<<endl;
    cin >> x >> y;
    cout << x + y;
    
    return 0;
}
