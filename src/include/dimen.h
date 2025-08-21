#ifndef DIMEN_H
  #define DIMEN_H

  // void dimVec() (Two Versions)
  // size_t dimMat()
  // size_t dimMatUppTrian()
  // size_t dimMatLowTrian()
  // size_t dimMatVarBandW()
  // void freeVec() (Two Versions)
  // void freeMat() (Two Versions)

  #include<iostream>
  using std::cout;
  using std::endl;

  #include<cstdlib>
  //using std::exit;

  #include <new>

  template <class T, class E1, class E2>
  void dimVec(T *(&v), const E1 offset, const E2 size)
  {
    v = new T [size]();
    if (!v) {
      cout << "No enough memory to create this vector.\n";
      exit (1);
    }
/*
    T *temp = &(v[-1]);
    for(E2 i=1; i <= size ;++i ) {
      *++temp = 0;
    } // endfor //
*/    
    v -= offset;
  } // end of dimVec() //


  template <class T, class E2>
  void dimVec(T *(&v), const E2 size)
  {
    dimVec(v,1,size);
  } // end of dimVec() //

  template <class T, class T1,class T2,class T3,class T4>
  size_t dimMat(T **(&m),
	        const T1 rowStart,
	        const T2 rowEnd,
	        const T3 colStart,
	        const T4 colEnd)
  {
    size_t totRows, totCols;
    totRows = rowEnd+1-rowStart;
    totCols = colEnd+1-colStart;
    const size_t lengthOfArray = totRows*totCols;

    m = (T **) new T* [totRows];
    if (!m) {
      cout << "No enough memory to create this matrix.\n";
      exit (1);
    }
    m -= rowStart;

    m[rowStart]= new T [lengthOfArray]();
    if (!m[rowStart]) {
      cout << "No enough memory to create this matrix.\n";
      exit (1);
    }
/*
    T *temp = &(m[rowStart][-1]);
    for(size_t i=1;i<=lengthOfArray; ++i ) {
      *++temp = 0;
      //      *++temp = i;
    } // endfor //
*/
    m[rowStart] -= colStart;
    for(T1 i=rowStart+1;i<=rowEnd ;++i ) {
      m[i] = m[i-1]+totCols;
    } // endfor //
    return (lengthOfArray);
  }

  template <class T, class T2,class T4>
  size_t dimMat(T **(&m),
	        const T2 rowEnd,
	        const T4 colEnd)
  {
    //   const size_t one=1;
    return dimMat(m,static_cast<T2>(1),rowEnd,static_cast<T4>(1),colEnd);
  }

  // Full Upper Triangular Matrix
  template <class T, class E>
  size_t dimMatUppTrian(T **(&m), const E rows)
  {
    const size_t lengthOfArray = rows  * (rows+1) /2;

    m = (T **) new T* [rows];
    if (!m) {
      cout << "No enough memory for this matrix.\n";
      exit (1);
    }
    m -= 1;

    m[1]= new T [lengthOfArray];
    if (!m[1]) {
      cout << "No enough memory for this matrix.\n";
      exit (1);
    }

    T *temp = &(m[1][-1]);
    for(size_t i=1;i<=lengthOfArray ; ++i ) {
      *++temp = 0;
      //      *++temp = i;
    } // endfor //

    m[1] -= 1;
    size_t width = rows-1;
    for(size_t i=2;i<=rows;++i) {
      m[i] = m[i-1] + width;
      --width;
    } // endfor //
    return (lengthOfArray);
  }

  // Full Lower Triangular Matrix
  template <class T, class E>
  size_t dimMatLowTrian(T **(&m), const E rows)
  {
    const size_t lengthOfArray = rows  * (rows+1) /2;

    m = (T **) new T* [rows];
    if (!m) {
      cout << "No enough memory for this matrix.\n";
      exit (1);
    }
    m -= 1;

    m[1]= new T [lengthOfArray];
    if (!m[1]) {
      cout << "No enough memory for this matrix.\n";
      exit (1);
    }

    T *temp = &(m[1][-1]);
    for(size_t i=1;i<=lengthOfArray ; ++i ) {
      *++temp = 0;
      //      *++temp = i;
    } // endfor //

    m[1] -= 1;
    size_t width = 1;
    for(size_t i=2;i<=rows;++i) {
      m[i] = m[i-1] + width;
      ++width;
    } // endfor //
    return (lengthOfArray);
  }

/*
  template <class R, class E, class E1>
  // Variable bandwith lower matrix
  #ifdef __WATCOM_CPLUSPLUS__
    size_t dimMatVarBandW( R **(&m),  const E1 rows, E *(&leftCol))
  #else
    size_t dimMatVarBandW( R **(&m),  const E1 &rows, E *(&leftCol))
  #endif
*/

  template <class R, class E1, class E2>
  size_t dimMatVarBandW( R **(&m),  const E1 &rows, E2 *(&leftCol))
  {
    auto lengthOfArray=rows;

    m = (R **) new R* [rows];
    if (!m) {
      cout << "No enough memory to create this Matrix.\n";
      exit (1);
    }
    m -= 1;

    for(E1 i=1 ;i<=rows ; ++i) {
      lengthOfArray += (i-leftCol[i]);
    } // endfor //

    m[1]= new R [lengthOfArray];
    if (!m[1]) {
      cout << "No enough memory to create this Matrix.\n";
      exit (1);
    }

    R *temp = &(m[1][-1]);
    for(E1 i=1;i<=lengthOfArray ;++i ) {
      *++temp = 0;
      //      *++temp = i;
    } // endfor //
    m[1] -= 1;

    E2 *temp1;
    temp1 = &(leftCol[1]);
    for(E2 i=2;i<=rows;++i) {
      m[i] = m[i-1] + (i+1 - *++temp1);
    } // endfor //

    for(E2 i=2;i<= rows; ++i ) {
      m[i] -= i-1;
    } // endfor //
    return (lengthOfArray);
  } // end of dimMatVarBandW() //

  template <class T, class E>
  void freeVec(T *(&v),const E offset)
  {
    delete [] (v+offset);
    v=nullptr;
  }
  template <class T>
  void freeVec(T *(&v))
  {
     freeVec(v,static_cast<int>(1));
    //delete [] (v+1);
  }

  template <class T, class T1, class T2>
  //void freeMat(T **(&m), const size_t rowStart=1, const size_t colStart=1) to be used when templates allow initial values
  void freeMat(T **(&m), const T1 rowStart, const T2 colStart)
  {
    m[rowStart] += colStart;
    delete m[rowStart];
    m += rowStart;
    delete [] m;
    m=nullptr;
  }

  template <class T>
  // meanwhile this is faking initial values
  void freeMat(T **(&m))
  {
    //   const size_t one=1;
    freeMat(m,1,1);
  }
#endif // End of dinen.h

/*
  Legacy code:

  used to store a constant banded symetric matrix as a rectangular matrix
  without loosing memory in the bottom of the (bandW-1) bottom rows.

  The saving in memory is not that big, therefore it is recomended to use
  dimMat() instead.

  // Constant bandwith upper matrix
  // saving elements from the diagonal to the right
  template <class T, class T1,class T2,class T3,class T4>
  void dimMatConstBandWUp(T **(&m),
  const T1 nrl,
  const T2 rows,
  const T3 ncl,
  const T4 bandW)
  {
  size_t i, nrh;
  const size_t lengthOfArray = bandW*(2*rows + 1 - bandW) /  2;
  nrh=rows+nrl-1;
  m = (T **) new T* [rows];
  if (!m) {
  cout << "No enough memory to create this Matrix.\n";
  exit (1);
  }
  m -= nrl;

  m[nrl]= new T [lengthOfArray];
  if (!m[nrl]) {
  cout << "No enough memory to create this Matrix.\n";
  exit (1);
  }

  T *temp = &(m[nrl][-1]);
  for(i=1;i<=lengthOfArray ;++i ) {
  *++temp = 0;
  //      *++temp = i;
  } // endfor //
  m[nrl]-= ncl;
  size_t width = bandW;
  size_t k=1,limit=rows+1-bandW;
  for(i=nrl+1;i<=nrh;++i) {
  m[i] = m[i-1]+width;
  if (++k > limit) {
  --width;
  } // endif //
  } // endfor //
  }
*/
