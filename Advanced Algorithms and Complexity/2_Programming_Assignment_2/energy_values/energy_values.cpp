/**
 * @file energy_values.cpp
 * @author Hovhannes Mikayelyan(@hovmikayelyan)
 * @brief 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

constexpr int PRECISION = 10;

using Column = std::vector<double>;
using Row = std::vector<double>;
using Matrix = std::vector<Row>;

struct Equation
{
    Matrix a;
    Column b;
};

struct Position
{
    short column;
    short row;
};

Equation ReadEquation()
{
    int size;
    std::cin >> size;

    Matrix a(size, std::vector<double>(size, 0.0));
    Column b(size, 0.0);

    for (int row = 0; row < size; ++row)
    {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }

    return Equation{std::move(a), std::move(b)};
}

Position SelectPivot(const Matrix &a, std::vector<bool> &used_rows, std::vector<bool> &used_columns)
{
    Position PivElement{0, 0};
    while (used_rows[PivElement.row])
    {
        ++PivElement.row;
    }
    while (used_columns[PivElement.column])
    {
        ++PivElement.column;
    }

    double max = 0.0;
    for (int from = PivElement.row, size = a.size(); from < size; ++from)
    {
        if (std::fabs(a[from][PivElement.column]) > std::fabs(max))
        {
            max = a[from][PivElement.column];
            PivElement.row = from;
        }
    }

    return PivElement;
}

inline void SwapLines(Matrix &a, Column &b, std::vector<bool> &used_rows, Position &PivElement)
{
    std::swap(a[PivElement.column], a[PivElement.row]);
    std::swap(b[PivElement.column], b[PivElement.row]);
    std::swap(used_rows[PivElement.column], used_rows[PivElement.row]);
    PivElement.row = PivElement.column;
}

void BackSubsitution(Matrix &a, Column &b)
{
    for (int i = a.size() - 1; i; --i)
    {
        double v = b[i];
        for (int j = 0; j != i; ++j)
        {
            b[j] -= a[j][i] * v;
            a[j][i] = 0;
        }
    }
}

inline void ScalePivot(Matrix &a, Column &b, const Position &PivElement)
{
    const double divisor = a[PivElement.row][PivElement.column];
    const int size = a.size();

    for (int j = PivElement.column; j < size; ++j)
    {
        a[PivElement.row][j] /= divisor;
    }

    b[PivElement.row] /= divisor;
}

void ProcessPivot(Matrix &a, Column &b, const Position &PivElement)
{
    const int size = a.size();
    double multiple{0.0};

    ScalePivot(a, b, PivElement);

    for (int i = PivElement.row + 1; i < size; ++i)
    {
        multiple = a[i][PivElement.column];
        for (int j = PivElement.column; j < size; ++j)
        {
            a[i][j] -= (a[PivElement.row][j] * multiple);
        }
        b[i] -= (b[PivElement.row] * multiple);
    }
}

inline void MarkPivotUsed(const Position &pivot, std::vector<bool> &used_rows, std::vector<bool> &used_columns)
{
    used_rows[pivot.row] = true;
    used_columns[pivot.column] = true;
}

Column SolveEquation(Equation equation)
{
    Matrix &a = equation.a;
    Column &b = equation.b;

    std::vector<bool> used_columns(a.size(), false);
    std::vector<bool> used_rows(a.size(), false);

    for (int steps = a.size(); steps; --steps)
    {
        Position PivElement = SelectPivot(a, used_rows, used_columns);
        SwapLines(a, b, used_rows, PivElement);
        ProcessPivot(a, b, PivElement);
        MarkPivotUsed(PivElement, used_rows, used_columns);
    }

    BackSubsitution(a, b);

    return b;
}

void PrintColumn(const Column &column)
{
    std::cout.precision(PRECISION);

    for (const auto s : column)
    {
        std::cout << s << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    Equation equation = ReadEquation();

    if (equation.a.size())
    {
        Column solution = SolveEquation(equation);
        PrintColumn(solution);
    }

    return 0;
}