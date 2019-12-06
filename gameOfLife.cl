__kernel void golKernel(__global int* gamestate, __global int* newstate, int x, int y) {
    int i = get_global_id(0);

    int topAdd;
	int bottomSub;
	int sum = 0;

	if (i < x) {
		topAdd = (x * y);
		bottomSub = 0;
	}
	else if (i >= (x * y) - x)
	{
		bottomSub = -(x * y);
		topAdd = 0;
	}
	else
	{
		topAdd = 0;
		bottomSub = 0;
	}

	if (i % x == 0)
	{
		sum += gamestate[i - 1 + topAdd];
		sum += gamestate[i + x - 1];
		sum += gamestate[i + x + x - 1 + bottomSub];
		sum += gamestate[i - x + 1 + topAdd];
		sum += gamestate[i + 1];
		sum += gamestate[i + x + 1 + bottomSub];
	}
	else if (i % x == x - 1) {

		sum += gamestate[i - x - x + 1 + topAdd];
		sum += gamestate[i - x + 1];
		sum += gamestate[i + 1 + bottomSub];
		sum += gamestate[i - x - 1 + topAdd];
		sum += gamestate[i - 1];
		sum += gamestate[i + x - 1 + bottomSub];

	}
	else
	{
		sum += gamestate[i - x - 1 + topAdd];
		sum += gamestate[i - x + 1 + topAdd];
		sum += gamestate[i - 1];
		sum += gamestate[i + 1];
		sum += gamestate[i + x - 1 + bottomSub];
		sum += gamestate[i + x + 1 + bottomSub];
	}


	sum += gamestate[i - x + topAdd];
	sum += gamestate[i + x + bottomSub];

    if (sum == 3) newstate[i] = 1;
    else if (sum == 2) newstate[i] = gamestate[i];
    else newstate[i] = 0;
}