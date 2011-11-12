class CountingSeries {
public:

long long countThem(long long a, long long b, long long c, long long d, long long upperBound) {
    long long total = (upperBound - a) / b;
    
    if (total >= 0) {
        if (a <= upperBound) {
            total++;
        }
    } else {
        total = 0;
    }
    
    long long geo = c;
    while (geo <= upperBound) {
        if (geo < a || ((geo-a) % b != 0)) {
            total++;
        }
        geo *= d;
        if (d == 1) {
            return total;
        }
    }
    return total;
}
};
