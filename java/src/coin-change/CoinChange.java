/*
 * MIT License
 *
 * Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @brief Solves the Coin Change Problem.
 *
 * @author João Caram and Pedro Henrique Penna.
 */
public class CoinChange
{
	public static int value = 0;
	public static int count = 0;
	public static List<Integer> sortedCoins;

	/**
	 * @brief Greedy algorithm.
	 *
	 * @param coins List of coins.
	 * @param change Target change.
	 *
	 * @return The number of coins in the solution.
	 */
	static int greedy(int[] coins, int change)
	{
		Arrays.sort(coins);

		sortedCoins = new ArrayList<Integer>();

		int pos = coins.length - 1;

		// Take a look in our money.
		while ((pos >= 0) && (value < change))
		{
			// Select this coin.
			if ((coins[pos] + value) <= change) {
				sortedCoins.add(coins[pos]);
				value += coins[pos];
				count++;
				continue;
			}

			pos--;
		}

		return count;
	}
}
