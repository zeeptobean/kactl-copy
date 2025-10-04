//Cach 1: chuan bi n^2, truy van O(1), modulo bac ky
#define MAX   5050
int comb[MAX][MAX];

for (int i = 0; i < MAX; i++) {
	comb[0][i] = 1;
	comb[i][0] = 0;
}
comb[0][0] = 1;

for (int i = 1; i < MAX; i++) for (int j = 1; j < MAX; j++) {
	if (i > j) comb[i][j] = 0;
	if (i == j) comb[i][j] = 1;
	if (i < j) {
		comb[i][j] = comb[i][j - 1] + comb[i - 1][j - 1];
		if (comb[i][j] >= MOD) comb[i][j] -= MOD;
	}
}

//Cach 2: chuan bi O(n), truy van O(1), modulo nt lon
#define MAX   1000100
int frac[MAX], finv[MAX];

frac[0] = 1;
for (int i = 1; i < MAX; i++) frac[i] = 1LL * frac[i - 1] * i % MOD;
finv[MAX - 1] = pw(frac[MAX - 1], MOD - 2);
for (int i = MAX - 2; i >= 0; i--) finv[i] = 1LL * finv[i + 1] * (i + 1) % MOD;
int comb(int k, int n) {
	return k > n ? 0 : 1LL * frac[n] * finv[k] % MOD * finv[n - k] % MOD;
}

//Cach 3: chuan bi O(k), truy van O(k), modulo > k
int comb(int k, long long n) {
	int res = finv[k];
	for (int i = 0; i < k; i++) res = 1LL * (n - i) % MOD * res % MOD;
	return res;
}

//Cach 4: chuan bi O(n), query O(n/ln(n)), modulo bac ky. 
#define MAX 1000100
bool notPrime[MAX];
vector<int> primes;

//prime sieve
notPrime[0] = notPrime[1] = true;
for (int i = 2; 1LL * i * i < MAX; i++) if (!notPrime[i])
	for (int j = i * i; j < MAX; j += i) notPrime[j] = true;
for (int i = 2; i < MAX; i++) if (!notPrime[i]) primes.push_back(i);

int comb(int k, int n) {
	if (k > n) return 0;    
	int res = 1;
	for (int p : primes) {
		if (p > n) break;
		int exp = 0; //calcuate p exponentation
		for (long long tmp = p; tmp <= n; tmp *= p)
			exp += n / tmp - k / tmp - (n - k) / tmp;
		res = 1LL * res * pw(p, exp) % MOD;
    }
	return res;
}

//set up hihi
// c_cpp_properties.json
// {
//   "configurations": [{
//       "name": "Win32",
//       "includePath": ["${workspaceFolder}/*"],
//       "defines": ["_DEBUG","UNICODE","_UNICODE","LOCAL_FREOPEN"],
//       "cStandard": "gnu17",
//       "cppStandard": "gnu++17",
//       "compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
//       "intelliSenseMode": "windows-gcc-x64"
//   }],
//   "version": 4
// }
// launch.json
// {
//   "version": "0.2.0",
//   "configurations": [{
//     "name": "msys2-mingw gdb 11.3 launch",
//     "type": "cppdbg",
//     "request": "launch",
//     "program": "${fileDirname}/${fileBasenameNoExtension}.exe",
//     "args": [],
//     "cwd": "${fileDirname}",
//     "MIMode": "gdb",
//     "miDebuggerPath": "C:\\msys64\\ucrt64\\bin\\gdb.exe",
//     "setupCommands": [
//       {
//         "description": "Enable pretty-printing for gdb",
//         "text": "-enable-pretty-printing",
//         "ignoreFailures": false
//       }
//     ]
//   }]
// }
