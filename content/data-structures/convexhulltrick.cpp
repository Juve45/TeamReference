/**
 * Author: Cristian Vintur
 * Date: 2019-03-24
 * License: CC0
 * Description: Add lines of the form ax+b and query maximum. Lines should be sorted in increasing order of slope
 * Time: $O(\log N)$.
 */
template<class T = pll, class U = ll>
struct hull {
	struct frac {
		ll x, y;		
		frac(ll _x, ll _y) : x(_x), y(_y) {
			if(y < 0) x = -x, y = -y;
		}		
		bool operator <(const frac &other) const {
			return 1.0 * x * other.y < 1.0 * other.x * y;
		}
	};	
	frac inter(T l1, T l2) { return { l2.se - l1.se, l1.fi - l2.fi }; }

	int nr = 0;
	vector<T> v;
	void add(T line) {
		// change signs for min
		if(!v.empty() && v.back().fi == line.fi) {
			if(v.back().se < line.se) v.back() = line;
			return;
		}
		while(nr >= 2 && inter(line, v[nr - 2]) < inter(v[nr - 1], v[nr - 2])) --nr, v.pop_back();
		v.push_back(line);
		++nr;
	}
	U query(ll x) {
		int l, r, mid;
		for(l = 0, r = nr - 1; l < r; ) {
			mid = (l + r) / 2;
			if(inter(v[mid], v[mid + 1]) < frac(x, 1)) l = mid + 1;
			else r = mid;
		}
		// while(p + 1 < nr && eval(v[p + 1], x) < eval(v[p], x)) ++p;
		return v[l];
	}
	ll eval(T line, ll x) {
		return line.fi * x + line.se;
	}
};