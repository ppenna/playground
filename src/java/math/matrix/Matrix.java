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

import java.lang.IllegalArgumentException;

/**
 * @brief Integer Matrix
 *
 * @author Pedro Henrique Penna
 */
public class Matrix
{
	/**
	 * @brief Leaf size for Strassen's Algorithm.
	 */
	private static final int STRASSEN_LEAF_SIZE = 256;

	/**
	 * @brief Underlying elements.
	 */
	private int[][] elements;

	/**
	 * Matrix size.
	 */
	private int size;

	/**
	 * @brief Creates a matrix.
	 *
	 * @param size Size of the matrix.
	 */
	public Matrix(int size) throws IllegalArgumentException
	{
		if (size < 1) {
			throw new IllegalArgumentException("invalid matrix size");
		}

		this.size = size;
		this.elements = new int[size][size];
	}

	/**
	 * @brief Adds two matrices
	 *
	 * @param A First operand.
	 * @param B Second operand.
	 *
	 * @return A + B.
	 *
	 * @author Pedro Henrique Penna
	 */
	public static Matrix add(Matrix A, Matrix B)
	{
		int n = A.size;

		Matrix C = new Matrix(n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				C.elements[i][j] = A.elements[i][j] + B.elements[i][j];
			}
		}

		return (C);
	}

	/**
	 * @brief Subtracts two matrices
	 *
	 * @param A First operand.
	 * @param B Second operand.
	 *
	 * @return A - B.
	 */
	public static Matrix subtract(Matrix A, Matrix B)
	{
		int n = A.size;

		Matrix C = new Matrix(n);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				C.elements[i][j] = A.elements[i][j] - B.elements[i][j];
			}
		}

		return C;
	}

	/**
	 * @brief Multiplies two matrices using Naive Algorithm.
	 *
	 * @param A First operand.
	 * @param B Second operand.
	 *
	 * @return A*B.
	 *
	 * @author Pedro Henrique Penna
	 */
	public static Matrix naive(Matrix A, Matrix B)
	{
		int n = A.size;

		Matrix C = new Matrix(n);

		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {
				for (int j = 0; j < n; j++) {
					C.elements[i][j] += A.elements [i][k]*B.elements[k][j];
				}
			}
		}
		return (C);
	}

	/**
	 * @brief Multiplies two matrices using Strassen's Algorithm.
	 *
	 * @param A First operand.
	 * @param B Second operand.
	 *
	 * @return A*B.
	 *
	 * @author Pedro Henrique Penna
	 */
	public static Matrix strassen(Matrix A, Matrix B) {
		int size = A.size;

		// End of recursion.
		if (size <= STRASSEN_LEAF_SIZE) {
			return naive(A, B);
		}

		int newSize = size/2;

		// Matrices A
		Matrix a11 = new Matrix(newSize);
		Matrix a12 = new Matrix(newSize);
		Matrix a21 = new Matrix(newSize);
		Matrix a22 = new Matrix(newSize);

		// Matrices B
		Matrix b11 = new Matrix(newSize);
		Matrix b12 = new Matrix(newSize);
		Matrix b21 = new Matrix(newSize);
		Matrix b22 = new Matrix(newSize);

		// Temp Matrices
		Matrix aResult = new Matrix(newSize);
		Matrix bResult = new Matrix(newSize);

		// Split matrix.
		for (int i = 0; i < newSize; i++) {
			for (int j = 0; j < newSize; j++) {
				a11.elements[i][j] = A.elements[i][j];                     // top left
				a12.elements[i][j] = A.elements[i][j + newSize];           // top right
				a21.elements[i][j] = A.elements[i + newSize][j];           // bottom left
				a22.elements[i][j] = A.elements[i + newSize][j + newSize]; // bottom right

				b11.elements[i][j] = B.elements[i][j];                     // top left
				b12.elements[i][j] = B.elements[i][j + newSize];           // top right
				b21.elements[i][j] = B.elements[i + newSize][j];           // bottom left
				b22.elements[i][j] = B.elements[i + newSize][j + newSize]; // bottom right
			}
		}

		// p1 = (a11 + a22)*(b11 + b22)
		aResult = add(a11, a22);
		bResult = add(b11, b22);
		Matrix p1 = strassen(aResult, bResult);

		// p2 = (a21 + a22)*(b11)
		aResult = add(a21, a22);
		Matrix p2 = strassen(aResult, b11);

		// p3 = (a11)*(b12 - b22)
		bResult = subtract(b12, b22);
		Matrix p3 = strassen(a11, bResult);

		// p4 = (a22)*(b21 - b11)
		bResult = subtract(b21, b11);
		Matrix p4 = strassen(a22, bResult);

		// p5 = (a11 + a12)*(b22)
		aResult = add(a11, a12);
		Matrix p5 = strassen(aResult, b22);

		// p6 = (a21 - a11)*(b11 + b12)
		aResult = subtract(a21, a11);
		bResult = add(b11, b12);
		Matrix p6 = strassen(aResult, bResult);

		// p7 = (a12-a22)*(b21+b22)
		aResult = subtract(a12, a22);
		bResult = add(b21, b22);
		Matrix p7 = strassen(aResult, bResult);

		// c12 = p3 + p5
		Matrix c12 = add(p3, p5);

		// c21 = p2 + p4
		Matrix c21 = add(p2, p4);

		// c11 = p1 + p4 - p5 + p7
		aResult = add(p1, p4);
		bResult = add(aResult, p7);
		Matrix c11 = subtract(bResult, p5);

		// c22 = p1 + p3 - p2 + p6
		aResult = add(p1, p3);
		bResult = add(aResult, p6);
		Matrix c22 = subtract(bResult, p2);

		// Build resulting matrix.
		Matrix C = new Matrix(size);
		for (int i = 0; i < newSize; i++) {
			for (int j = 0; j < newSize; j++) {
				C.elements[i][j] = c11.elements[i][j];
				C.elements[i][j + newSize] = c12.elements[i][j];
				C.elements[i + newSize][j] = c21.elements[i][j];
				C.elements[i + newSize][j + newSize] = c22.elements[i][j];
			}
		}

		return (C);
	}
}
