// ------------------------------------------------------------------------
//
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2014 - 2020 by the deal.II authors
//
// This file is part of the deal.II library.
//
// Part of the source code is dual licensed under Apache-2.0 WITH
// LLVM-exception OR LGPL-2.1-or-later. Detailed license information
// governing the source code and code contributions can be found in
// LICENSE.md and CONTRIBUTING.md at the top level directory of deal.II.
//
// ------------------------------------------------------------------------


// test LAPACKFullMatrix::vmult() and Tvmult() for triangular matrices

/* MWE for size=3 in Octave:
R = [1,2,3; 0, 5, 6; 0, 0, 9]
x = [2; -7; 1]

> R*x
ans =

   -9
  -29
    9

R' * x
ans =

    2
  -31
  -27
*/

#include <deal.II/lac/full_matrix.h>
#include <deal.II/lac/lapack_full_matrix.h>
#include <deal.II/lac/vector.h>

#include <iostream>

#include "../tests.h"

#include "create_matrix.h"


template <typename NumberType>
void
test()
{
  const unsigned int           size = 3;
  LAPACKFullMatrix<NumberType> M(size);
  M.set_property(LAPACKSupport::upper_triangular);

  M                    = 0.;
  unsigned int counter = 1;
  for (unsigned int i = 0; i < size; ++i)
    for (unsigned int j = 0; j < size; ++j)
      {
        if (j >= i)
          M(i, j) = counter;

        counter++;
      }

  Vector<NumberType> x(size), y(size);
  x[0] = 2;
  x[1] = -7;
  x[2] = 1;

  M.vmult(y, x);
  y.print(deallog.get_file_stream(), 6, false);

  M.Tvmult(y, x);
  y.print(deallog.get_file_stream(), 6, false);
}


int
main()
{
  initlog();
  deallog.get_file_stream().precision(3);

  test<double>();
}
