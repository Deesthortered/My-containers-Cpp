#pragma once
#include <vector>
#include <iostream>

namespace spaceMatrix
{
	template<class T>
	class Matrix
	{
		size_t height;
		size_t width;
		T** arr; // [������][�������]

	public:
		Matrix()
		{
			this->height = 0;
			this->width = 0;
			this->arr = nullptr;
		}
		Matrix(const Matrix &obj)
		{
			this->height = obj.height;
			this->width = obj.width;
			if (!this->height || !this->width) { this->arr = nullptr; return; }
			this->arr = new T*[this->height];
			for (register size_t i = 0; i < this->height; i++)
			{
				this->arr[i] = new T[this->width];
				for (register size_t j = 0; j < this->width; j++)
					this->arr[i][j] = obj.arr[i][j];
			}
		}
		Matrix(size_t h, size_t w, T value = T())
		{
			this->height = h;
			this->width = w;
			if (!this->height || !this->width) { this->arr = nullptr; return; }
			this->arr = new T*[h];
			for (register size_t i = 0; i < h; i++)
			{
				this->arr[i] = new T[w];
				for (register size_t j = 0; j < w; j++)
					this->arr[i][j] = value;
			}
		}
		Matrix(T** arr, size_t h, size_t w)
		{
			this->height = h;
			this->width = w;
			if (!this->height || !this->width) { this->arr = nullptr; return; }
			this->arr = new T*[h];
			for (register size_t i = 0; i < h; i++)
			{
				this->arr[i] = new T[w];
				for (register size_t j = 0; j < w; j++)
					this->arr[i][j] = arr[i][j];
			}
		}
		Matrix(std::vector<std::vector<T>> arr)
		{
			this->height = arr.size();
			this->width = arr[0].size();
			if (!this->height || !this->width) { this->arr = nullptr; return; }
			this->arr = new T*[this->height];
			for (register size_t i = 0; i < this->height; i++)
			{
				this->arr[i] = new T[this->width];
				for (register size_t j = 0; j < this->width; j++)
					this->arr[i][j] = arr[i][j];
			}
		}
		~Matrix()
		{
			deleteMatrix();
		}

		size_t Height()
		{
			return this->height;
		}
		size_t Width()
		{
			return this->width;
		}
		T &at(size_t i, size_t j)
		{
			if (i >= height || j >= width) throw "Out of range";
			return this->arr[i][j];
		}
		Matrix Transpose()
		{
			Matrix res(this->width, this->height, T());
			for (register size_t i = 0; i < this->height; i++)
				for (register size_t j = 0; j < this->width; j++)
					res.arr[j][i] = this->arr[i][j];
			return res;
		}
		static Matrix UseFuncToElems(Matrix m, T(*func)(T))
		{
			for (register size_t i = 0; i < m.height; i++)
				for (register size_t j = 0; j < m.width; j++)
					m.arr[i][j] = (*func)(m.arr[i][j]);
			return m;
		}

		Matrix& operator=(const Matrix &obj)
		{
			if (&obj == this) return *this;
			deleteMatrix();
			this->height = obj.height;
			this->width = obj.width;
			if (!this->height || !this->width) { this->arr = nullptr; return *this; }
			this->arr = new T*[this->height];
			for (register size_t i = 0; i < this->height; i++)
			{
				this->arr[i] = new T[this->width];
				for (register size_t j = 0; j < this->width; j++)
					this->arr[i][j] = obj.arr[i][j];
			}
			return *this;
		}
		friend bool operator==(const Matrix& a, const Matrix& b)
		{
			if (a.height != b.height || a.width != b.width) return false;
			for (register size_t i = 0; i < a.height; i++)
				for (register size_t j = 0; j < a.width; j++)
					if (a.arr[i][j] != b.arr[i][j]) return false;
			return true;
		}

		friend const Matrix operator+(const Matrix& a, const Matrix& b)
		{
			if (a.height != b.height || a.width != b.width) throw "Matrices are not compatible";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] + b.arr[i][j];
				return res;
			}
		}
		friend const Matrix operator+(const Matrix& a, const T& b)
		{
			if (!a.height || !a.width) throw "Matrix is empty";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] + b;
				return res;
			}
		}
		friend const Matrix operator+(const T& b, const Matrix& a)
		{
			if (!a.height || !a.width) throw "Matrix is empty";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] + b;
				return res;
			}
		}

		friend const Matrix operator-(const Matrix& a, const Matrix& b)
		{
			if (a.height != b.height || a.width != b.width) throw "Matrices are not compatible";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] - b.arr[i][j];
				return res;
			}
		}
		friend const Matrix operator-(const Matrix& a, const T& b)
		{
			if (!a.height || !a.width) throw "Matrix is empty";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] - b;
				return res;
			}
		}
		friend const Matrix operator-(const T& b, const Matrix& a)
		{
			if (!a.height || !a.width) throw "Matrix is empty";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = b - a.arr[i][j];
				return res;
			}
		}

		friend const Matrix operator*(const Matrix& a, const Matrix& b)
		{
			if (a.width != b.height) throw "Matrices are not compatible";
			else
			{
				Matrix res(a.height, b.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < b.width; j++)
						for (register size_t k = 0; k < a.width; k++)
							res.arr[i][j] += a.arr[i][k] * b.arr[k][j];
				return res;
			}
		}
		friend const Matrix operator*(const Matrix& a, const T& b)
		{
			if (!a.height || !a.width) throw "Matrix is empty";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] * b;
				return res;
			}
		}
		friend const Matrix operator*(const T& b, const Matrix& a)
		{
			if (!a.height || !a.width) throw "Matrix is empty";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] * b;
				return res;
			}
		}

		friend const Matrix operator&(const Matrix& a, const Matrix& b)
		{
			if (a.height != b.height || a.width != b.width) throw "Matrices are not compatible";
			else
			{
				Matrix res(a.height, a.width, T());
				for (register size_t i = 0; i < a.height; i++)
					for (register size_t j = 0; j < a.width; j++)
						res.arr[i][j] = a.arr[i][j] * b.arr[i][j];
				return res;
			}
		}
		Matrix& operator&=(const Matrix a)
		{
			if (a.height != this->height || a.width != this->width) throw "Matrices are not compatible";
			else
			{
				for (register size_t i = 0; i < this->height; i++)
					for (register size_t j = 0; j < this->width; j++)
						this->arr[i][j] *= a.arr[i][j];
			}
			return *this;
		}

		Matrix& operator+=(const Matrix a)
		{
			if (a.height != this->height || a.width != this->width) throw "Matrices are not compatible";
			else
			{
				for (register size_t i = 0; i < this->height; i++)
					for (register size_t j = 0; j < this->width; j++)
						this->arr[i][j] += a.arr[i][j];
			}
			return *this;
		}
		Matrix& operator+=(const T& a)
		{
			if (!this->height || !this->width) throw "Matrix is empty";
			else
			{
				for (register size_t i = 0; i < this->height; i++)
					for (register size_t j = 0; j < this->width; j++)
						this->arr[i][j] += a;
			}
			return *this;
		}

		Matrix& operator-=(const Matrix a)
		{
			if (a.height != this->height || a.width != this->width) throw "Matrices are not compatible";
			else
			{
				for (register size_t i = 0; i < this->height; i++)
					for (register size_t j = 0; j < this->width; j++)
						this->arr[i][j] -= a.arr[i][j];
			}
			return *this;
		}
		Matrix& operator-=(const T& a)
		{
			if (!this->height || !this->width) throw "Matrix is empty";
			else
			{
				for (register size_t i = 0; i < this->height; i++)
					for (register size_t j = 0; j < this->width; j++)
						this->arr[i][j] -= a;
			}
			return *this;
		}

		Matrix& operator*=(const Matrix a)
		{
			if (this->width != a.height) throw "Matrices are not compatible";
			else
			{
				Matrix res(this->height, a.width, T());
				for (register size_t i = 0; i < this->height; i++)
					for (register size_t j = 0; j < a.width; j++)
						for (register size_t k = 0; k < this->width; k++)
							res.arr[i][j] += this->arr[i][k] * a.arr[k][j];
				*this = res;
			}
			return *this;
		}
		Matrix& operator*=(const T& a)
		{
			if (!this->height || !this->width) throw "Matrix is empty";
			else
			{
				for (register size_t i = 0; i < this->height; i++)
					for (register size_t j = 0; j < this->width; j++)
						this->arr[i][j] *= a;
			}
			return *this;
		}

		void Show()
		{
			if (!this->height || !this->width) { cout << "Matrix is empty" << endl; return; }
			for (register size_t i = 0; i < this->height; i++)
			{
				for (register size_t j = 0; j < this->width; j++)
					cout << this->arr[i][j] << " ";
				cout << endl;
			}
			cout << endl << endl;
		}
	private:
		void deleteMatrix()
		{
			if (!this->height || !this->width) return;
			for (register size_t i = 0; i < height; i++)
				delete[] this->arr[i];
			delete[] this->arr;
			this->height = 0;
			this->width = 0;
		}
	};
}