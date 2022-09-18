SEED = chrono::steady_clock::now().time_since_epoch().count();
// or use `high_resolution_clock`
random_device rd; auto SEED = rd();
mt19937 rng(SEED);
uniform_int_distribution<> dis(MIN, MAX); // usage: dis(rng)
// others: uniform_real_distribution,
