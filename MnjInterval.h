#pragma once
#include "MathConstant.h"
class  MnjInterval
{
public:

  static const MnjInterval EmptyInterval; // (MNJ_UNSET_VALUE,MNJ_UNSET_VALUE)

  ////////
  // The default constructor creates an empty interval (MNJ_UNSET_VALUE,MNJ_UNSET_VALUE)
  MnjInterval();

  MnjInterval(double t0,double t1);

  ~MnjInterval();

  bool operator!=(const MnjInterval&) const;
  bool operator==(const MnjInterval&) const;

  // Interval = [m_t[0], m_t[1]]
  double m_t[2];

  /*
  Description:
    Sets interval to (MNJ_UNSET_VALUE,MNJ_UNSET_VALUE)
  See Also:
    MnjInterval::Set
  */
  void Destroy();

  /*
  Description:
    Sets interval to [t0,t1]
  Parameters:
    t0 - [in]
    t1 - [in]
  See Also:
    MnjInterval::MnjInterval( double, double )
  */
  void Set(
    double t0, 
    double t1
    );

  /*
  Description:
    Convert normalized parameter to interval value, or pair of values.
  Parameters:
    normalized_parameter - [in] 
  Returns:
    Interval parameter
    min*(1.0-normalized_parameter) + max*normalized_parameter
  See Also:
    MnjInterval::NormalizedParameterAt
  */
  double ParameterAt (
    double normalized_parameter
    ) const; 
  MnjInterval ParameterAt (
    MnjInterval normalized_interval
    ) const; 
  
  /*
  Description:
    Convert interval value, or pair of values, to normalized parameter.
  Parameters:
    interval_parameter - [in] value in interval
  Returns:
    Normalized parameter x so that 
    min*(1.0-x) + max*x = interval_parameter.
  See Also:
    MnjInterval::ParameterAt
  */
  double NormalizedParameterAt (
    double interval_parameter
    ) const;
  MnjInterval NormalizedParameterAt (
    MnjInterval interval_parameter
    ) const;

  double& operator[](int); // returns (index<=0) ? m_t[0] : m_t[1]
  double operator[](int) const; // returns (index<=0) ? m_t[0] : m_t[1]

  double Min() const; // returns smaller of m_t[0] and m_t[1]
  double Max() const; // returns larger of m_t[0] and m_t[1]
  double Mid() const; // returns 0.5*(m_t[0] + m_t[1])
  double Length() const;

  bool IsIncreasing() const; // returns true if m_t[0] < m_t[1]
  bool IsDecreasing() const; // returns true if m_t[0] > m_t[0];
  bool IsInterval() const;   // returns truc if m_t[0] != m_t[1]
  bool IsSingleton() const;  // returns true if m_t[0] == m_t[1] != MNJ_UNSET_VALUE
  bool IsEmptyInterval() const;   // returns true if m_t[0] == m_t[1] == MNJ_UNSET_VALUE
  bool IsValid() const;      // returns ON_IsValid(m_t[0]) && ON_IsValid(m_t[1])

  // OBSOLETE - Use IsEmptyInterval()
  bool IsEmptySet() const;   // returns true if m_t[0] == m_t[1] == MNJ_UNSET_VALUE

	bool MakeIncreasing();		// returns true if resulting interval IsIncreasing() 

  /*
  Returns:
    @untitled table
     0      this is idential to other
    -1      this[0] < other[0]
    +1      this[0] > other[0]
    -1      this[0] == other[0] and this[1] < other[1]
    +1      this[0] == other[0] and this[1] > other[1]
  */
  int Compare( const MnjInterval& other ) const;

  /* 
  Description:
    Test a value t to see if it is inside the interval.
  Parameters:
    t - [in] value to test
    bTestOpenInterval - [in] 
        If false, t is tested to see if it satisfies min <= t <= max.
        If true, t is tested to see if it satisfies min < t < max.
  Returns:
    true if t is in the interval and false if t is not
    in the interval.
  */
  bool Includes(
    double t,
    bool bTestOpenInterval = false
    ) const;

  /* 
  Description:
    Test an interval to see if it is contained in this interval.
  Parameters:
    other - [in] interval to test
    bProperSubSet - [in] if true, then the test is for a proper subinterval.
  Returns:
    If bProperSubSet is false, then the result is true when
    this->Min() <= other.Min() and other.Max() <= this->Max().
    If bProperSubSet is true, then the result is true when
    this->Min() <= other.Min() and other.Max() <= this->Max()
    and at least one of the inequalites is strict.
  */
  bool Includes( 
    const MnjInterval& other,
    bool bProperSubSet = false
    ) const;

  /*
  Description:
    Changes interval to [-m_t[1],-m_t[0]].
  */
  void Reverse();

  /*
  Description:
    Swaps m_t[0] and m_t[1].
  */
  void Swap();

  //////////
  // If the intersection is not empty, then 
  // intersection = [max(this.Min(),arg.Min()), min(this.Max(),arg.Max())]
  // Intersection() returns true if the intersection is not empty.
  // The interval [MNJ_UNSET_VALUE,MNJ_UNSET_VALUE] is considered to be
  // the empty set interval.  The result of any intersection involving an
  // empty set interval or disjoint intervals is the empty set interval.
  bool Intersection( // this = this intersect arg
         const MnjInterval&
         );

  //////////
  // If the intersection is not empty, then 
  // intersection = [max(argA.Min(),argB.Min()), min(argA.Max(),argB.Max())]
  // Intersection() returns true if the intersection is not empty.
  // The interval [MNJ_UNSET_VALUE,MNJ_UNSET_VALUE] is considered to be
  // the empty set interval.  The result of any intersection involving an
  // empty set interval or disjoint intervals is the empty set interval.
  bool Intersection( // this = intersection of two args
         const MnjInterval&, 
         const MnjInterval&
         );

  //////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
  // union = [min(this.Min(),arg.Min()), max(this.Max(),arg.Max()),]
  // Union() returns true if the union is not empty.
  bool Union( // this = this union arg
         const MnjInterval&
         );

  //////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
  // union = [min(argA.Min(),argB.Min()), max(argA.Max(),argB.Max()),]
  // Union() returns true if the union is not empty.
  bool Union( // this = union of two args
         const MnjInterval&, 
         const MnjInterval&
         );
};
