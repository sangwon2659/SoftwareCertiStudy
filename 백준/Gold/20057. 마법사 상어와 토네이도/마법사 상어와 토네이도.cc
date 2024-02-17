#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	// For debugging purposes
	/*
	// Read text file
	ifstream txt_input("input.txt");

	// Acquire the size of the base map
	int testcase;
	txt_input >> testcase;

	// Insert base map info from the text file
	vector<vector<int>> base_map(testcase, vector<int>(testcase));
	for (int r = 0; r < testcase; r++)
		for (int c = 0; c < testcase; c++)
			txt_input >> base_map[r][c];
	*/

	// Get data directly from platform
	// Get size of the base map
	int testcase;
	cin >> testcase;

	// Store data in a 2D vector
	vector<vector<int>> base_map(testcase, vector<int>(testcase));
	for (int r = 0; r < testcase; r++)
		for (int c = 0; c < testcase; c++)
			cin >> base_map[r][c];

	// Compute the center point of the base map
	int pos_x, pos_y;
	pos_x = testcase / 2;
	pos_y = testcase / 2;

	// Hardcode the ratiomaps w.r.t. the directions [W, S, E, N]
	vector<vector<float>> ratiomap_library =
	{
		{0, 0, 0.02, 0, 0, 0, 0.10, 0.07, 0.01, 0, 0.05, 1, 1, 1, 0, 0, 0.1, 0.07, 0.01, 0, 0, 0, 0.02, 0, 0}, // West
		{0, 0, 0, 0, 0, 0, 0.01, 1, 0.01, 0, 0.02, 0.07, 1, 0.07, 0.02, 0, 0.1, 1, 0.1, 0, 0, 0, 0.05, 0, 0,}, // South
		{0, 0, 0.02, 0, 0,  0, 0.01, 0.07, 0.1, 0, 0, 1, 1, 1, 0.05, 0, 0.01, 0.07, 0.1, 0, 0, 0, 0.02, 0, 0}, // East
		{0, 0, 0.05, 0, 0, 0, 0.1, 1, 0.1, 0, 0.02, 0.07, 1, 0.07, 0.02, 0, 0.01, 1, 0.01, 0, 0, 0, 0, 0, 0} // North
	};

	// Get total sand before the tornado computation
	int total_sand = 0;
	for (int r = 0; r < testcase; r++)
	{
		for (int c = 0; c < testcase; c++)
			total_sand += base_map[r][c];
	}

	// Declare variables to be used in the loop
	int cnt = 0;
	int cnt_decoder;
	int stride_length = 1;
	int temp_sand_sum = 0;
	vector<float> ratiomap;
	int target_pos_x = pos_x;
	int target_pos_y = pos_y;
	int idx = 0;
	bool condition = true;

	// Repeat until tornado reaches (0,0)
	while (condition)
	{
		// Compute the stride length
		if (cnt != 0 && cnt % 2 == 0) stride_length++;

		// Decode the cnt and select the ratiomap accordingly
		cnt_decoder = cnt % 4;
		ratiomap = ratiomap_library[cnt_decoder];

		// Repeat the computation until the desired stride length is reached
		for (int stride = 0; stride < stride_length; stride++)
		{
		        // Double break from the loops if tornado has reached (0,0)
			if (pos_x == 0 && pos_y == 0)
			{
				condition = false;
				break;
			}

			// Compute the direction of the stride
			switch (cnt_decoder)
			{
			case 0:
				target_pos_x = pos_x - 1;
				break;
			case 1:
				target_pos_y = pos_y + 1;
				break;
			case 2:
				target_pos_x = pos_x + 1;
				break;
			case 3:
				target_pos_y = pos_y - 1;
				break;
			}

			// Initialize repeated variables
			idx = 0;
			temp_sand_sum = base_map[target_pos_y][target_pos_x];

		        // Map the ratiomap onto the base_map and compute the values
			for (int r = target_pos_y - 2; r <= target_pos_y + 2; r++)
			{
				for (int c = target_pos_x - 2; c <= target_pos_x + 2; c++)
				{
				        // Subtract the mapped value from temp_sand_sum if it is over the boundaries of the base map
					if (r < 0 || r >= base_map.size() || c < 0 || c >= base_map.size())
					{
						temp_sand_sum -= (int)(base_map[target_pos_y][target_pos_x] * ratiomap[idx++]);
					}

					// Continue if the ratiomap idx is alpha, y or x
					else if (ratiomap[idx] == 1)
					{
						idx++;
						continue;
					}

					// Subtract the mapped value from temp_sand_sum and add the value to the base map if it is not over the boundaries of the base map
					else
					{
						temp_sand_sum -= (int)(base_map[target_pos_y][target_pos_x] * ratiomap[idx]);
            					base_map[r][c] += (int)(base_map[target_pos_y][target_pos_x] * ratiomap[idx++]);
					}
				}
			}

		        // Set the base map at target position as 0
			base_map[target_pos_y][target_pos_x] = 0;

		        // Update pos_x and pos_y
		        // Set the alpha value on the base map
			switch (cnt_decoder)
			{
			case 0:
				pos_x--;
				if (target_pos_x - 1 >= 0) base_map[target_pos_y][target_pos_x - 1] += temp_sand_sum;
				break;
			case 1:
				pos_y++;
				if (target_pos_y + 1 < base_map.size()) base_map[target_pos_y + 1][target_pos_x] += temp_sand_sum;
				break;
			case 2:
				pos_x++;
				if (target_pos_x + 1 < base_map.size()) base_map[target_pos_y][target_pos_x + 1] += temp_sand_sum;
				break;
			case 3:
				pos_y--;
				if (target_pos_y - 1 >= 0) base_map[target_pos_y - 1][target_pos_x] += temp_sand_sum;
				break;
			}	
		}

		// Increment cnt for every while loop (this happens with every change in direction)
		cnt++;
	}

  	// Compute the remaining sand on the base map
	int remaining_sand = 0;
	for (int r = 0; r < testcase; r++)
	{
		for (int c = 0; c < testcase; c++)
			remaining_sand += base_map[r][c];
	}

  	// Subtract the remaining sand from total sand and print it as the result
	cout << total_sand - remaining_sand << endl;

	return 0;
}

