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

import java.util.Stack;

/**
 * @brief Test driver for Subset Sum Problem.
 *
 * @author João Caram and Pedro Henrique Penna
 */
public class Main
{
	/**
	 * @brief Current sum.
	 */
	static int partialSum; 
 
	/**
	 * @brief Partial solution.
	 */
	static Stack partialSolution = new Stack<>();

	/**
	 * @brief Solves the Subset Sum Problem.
	 *
	 * @param S   Set
	 * @param d   Target sum
	 * @param pos Initial offset position in the set.
	 *
	 * @details This algorithm relies on backtracking.
	 */
	static void subsetSum(int[] S, int d, int pos)
	{
		int n = S.length;
		
		// Try all increasing subsets.
		for (int i = pos; i < n ; i++) {

			partialSolution.push(S[i]);
			partialSum += S[i];
			
			// Solution found.
			if (partialSum == d) {
				return;
			}
			// Try next element.
			else if (partialSum < d) {
				subsetSum(S, d, i + 1);
			}
			// Backtrack
			else { 
				partialSum -= (int) partialSolution.pop();
			}
		}

		partialSum -= (int)partialSolution.pop();
		
	}

	public static void main(String[] args) throws Exception
	{
		int[] S = {2, 4, 6, 1, 7, 8, 10, 5, 9, 11};
		int d = 42;

		partialSum=0;
		subsetSum(S, d, 0);
		System.out.println(partialSolution);
	}
}
