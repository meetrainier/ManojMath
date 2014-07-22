#include "MnjInterval.h"

const MnjInterval MnjInterval::EmptyInterval(MNJ_UNSET_VALUE,MNJ_UNSET_VALUE);

MnjInterval::MnjInterval()
{
  m_t[0] = m_t[1] = MNJ_UNSET_VALUE; 
}

MnjInterval::MnjInterval(double t0, double t1)
{
  Set(t0,t1);
}

MnjInterval::~MnjInterval()
{}

double&
MnjInterval::operator[](int i)
{
  return m_t[(i<=0)?0:1];
}

double
MnjInterval::operator[](int i) const
{
  return m_t[(i<=0)?0:1];
}

double
MnjInterval::Min() const
{
  return m_t[IsDecreasing()?1:0];
}

void MnjInterval::Destroy()
{
  Set(MNJ_UNSET_VALUE,MNJ_UNSET_VALUE);
}

void MnjInterval::Set(double t0,double t1)
{
  m_t[0] = t0;
  m_t[1] = t1;
}

double MnjInterval::ParameterAt(double x) const
{
  return (MNJ_IS_VALID(x) ? ((1.0-x)*m_t[0] + x*m_t[1]) : MNJ_UNSET_VALUE);
}

MnjInterval MnjInterval::ParameterAt(MnjInterval x) const
{
  return MnjInterval( ParameterAt(x[0]), ParameterAt(x[1]) );
}




double MnjInterval::NormalizedParameterAt( // returns x so that min*(1.0-x) + max*x = input
  double t
  ) const
{
  if (!MNJ_IS_VALID(t))
    return MNJ_UNSET_VALUE; // added 29 Sep 2006

  double x = m_t[0];
  if ( m_t[0] != m_t[1] ) {
    x = ( t == m_t[1]) ? 1.0 : (t - m_t[0])/(m_t[1] - m_t[0]);
  }
  return x;
}

MnjInterval MnjInterval::NormalizedParameterAt( // returns x so that min*(1.0-x) + max*x = input
  MnjInterval t
  ) const
{
	return  MnjInterval(	NormalizedParameterAt(t[0]) , 
												NormalizedParameterAt(t[1]) );
}
double
MnjInterval::Max() const
{
  return m_t[IsDecreasing()?0:1];
}

double
MnjInterval::Mid() const
{
  return 0.5*(m_t[0]+m_t[1]);
}

double
MnjInterval::Length() const
{
  return ( MNJ_IS_VALID(m_t[0]) && MNJ_IS_VALID(m_t[1]) ) ? m_t[1]-m_t[0] : 0.0;
}

bool
MnjInterval::IsIncreasing() const
{
  return ( m_t[0] < m_t[1] && MNJ_IS_VALID(m_t[0]) && MNJ_IS_VALID(m_t[1]) ) ? true : false;
}

bool
MnjInterval::IsDecreasing() const
{
  return ( m_t[0] > m_t[1] && MNJ_IS_VALID(m_t[0]) && MNJ_IS_VALID(m_t[1]) ) ? true : false;
}

bool
MnjInterval::IsInterval() const
{
  return ( m_t[0] != m_t[1] && MNJ_IS_VALID(m_t[0]) && MNJ_IS_VALID(m_t[1]) ) ? true : false;
}


bool
MnjInterval::IsSingleton() const
{
  return ( m_t[0] == m_t[1] && MNJ_IS_VALID(m_t[1]) ) ? true : false;
}

bool
MnjInterval::IsEmptyInterval() const
{
  return ( m_t[0] == MNJ_UNSET_VALUE && m_t[1] == MNJ_UNSET_VALUE ) ? true : false;
}

bool
MnjInterval::IsEmptySet() const
{
  return ( m_t[0] == MNJ_UNSET_VALUE && m_t[1] == MNJ_UNSET_VALUE ) ? true : false;
}

bool
MnjInterval::IsValid() const
{
  // 05/29/2007 TimH. Changed 0 to 1.
  return ( MNJ_IS_VALID(m_t[0]) && MNJ_IS_VALID(m_t[1]) );
}

bool 
MnjInterval::MakeIncreasing()		// returns true if resulting interval IsIncreasing() 
{
	if( IsDecreasing()){ 
		Swap();
		return true;
	}
	return IsIncreasing();
}

bool 
MnjInterval::operator!=(const MnjInterval& other) const
{
  return Compare(other) ? true : false;
}
bool 
MnjInterval::operator==(const MnjInterval& other) const
{
  return Compare(other) ? false : true;
}


int
MnjInterval::Compare( const MnjInterval& other ) const
{
  if ( m_t[0] < other.m_t[0] )
    return -1;
  if ( m_t[0] > other.m_t[0] )
    return 1;
  if ( m_t[1] < other.m_t[1] )
    return -1;
  if ( m_t[1] > other.m_t[1] )
    return 1;
  return 0;
}

bool
MnjInterval::Includes( double t, bool bTestOpenInterval) const
{
  bool rc = false;
  if ( MNJ_IS_VALID(t) && MNJ_IS_VALID(m_t[0]) && MNJ_IS_VALID(m_t[1]) )
  {
    int i = (m_t[0] <= m_t[1]) ? 0 : 1;
    if ( bTestOpenInterval )
    {
      rc = ( m_t[i] < t && t < m_t[1-i] ) ? true : false;
    }
    else
    {
      rc = ( m_t[i] <= t && t <= m_t[1-i] ) ? true : false;
    }
  }
  return rc;
}

bool
MnjInterval::Includes( const MnjInterval& other, bool bProperSubSet ) const
{
  bool rc = ( Includes( other.m_t[0] ) && Includes( other.m_t[1] ) ) ? true : false;
  if ( rc && bProperSubSet )
  {
    if ( !Includes( other.m_t[0], true ) && !Includes( other.m_t[1], true ) )
      rc = false;
  }
  return rc;
}

void
MnjInterval::Reverse()
{
  if ( !IsEmptySet() ) {
    const double x = -m_t[0];
    m_t[0] = -m_t[1];
    m_t[1] = x;
  }
}

void
MnjInterval::Swap()
{
  const double x = m_t[0];
  m_t[0] = m_t[1];
  m_t[1] = x;
}

//////////
// If the intersection is not empty, then 
// intersection = [max(this.Min(),arg.Min()), min(this.Max(),arg.Max())]
// Intersection() returns true if the intersection is not empty.
// The interval [MNJ_UNSET_VALUE,MNJ_UNSET_VALUE] is considered to be
// the empty set interval.  The result of any intersection involving an
// empty set interval or disjoint intervals is the empty set interval.
bool MnjInterval::Intersection( // this = this intersect arg
       const MnjInterval& other
       )
{
  bool rc = false;
  if ( IsEmptySet() && other.IsEmptySet() )
    Destroy();
  else {
    double a, b, mn, mx;
    a = Min();
    b = other.Min();
    mn = (a>=b) ? a : b;
    a = Max();
    b = other.Max();
    mx = (a<=b) ? a : b;
    if ( mn <= mx ) {
      Set(mn,mx);
      rc = true;
    }
    else
      Destroy();
  }
  return rc;
}

//////////
// If the intersection is not empty, then 
// intersection = [max(argA.Min(),argB.Min()), min(argA.Max(),argB.Max())]
// Intersection() returns true if the intersection is not empty.
// The interval [MNJ_UNSET_VALUE,MNJ_UNSET_VALUE] is considered to be
// the empty set interval.  The result of any intersection involving an
// empty set interval or disjoint intervals is the empty set interval.
bool MnjInterval::Intersection( // this = intersection of two args
       const MnjInterval& ain, 
       const MnjInterval& bin
       )
{
  bool rc = false;
  if ( ain.IsEmptySet() && bin.IsEmptySet() )
    Destroy();
  else {
    double a, b, mn, mx;
    a = ain.Min();
    b = bin.Min();
    mn = (a>=b) ? a : b;
    a = ain.Max();
    b = bin.Max();
    mx = (a<=b) ? a : b;
    if ( mn <= mx ) {
      Set(mn,mx);
      rc = true;
    }
    else
      Destroy();
  }
  return rc;
}

//////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
// union = [min(this.Min(),arg.Min()), max(this.Max(),arg.Max()),]
// Union() returns true if the union is not empty.
bool MnjInterval::Union( // this = this union arg
       const MnjInterval& other
       )
{
  bool rc = false;
  if ( other.IsEmptySet() ) {
    // this may be increasing, decreasing, or empty
    Set( Min(), Max() );
    rc = !IsEmptySet();
  }
  else if ( IsEmptySet() ) {
    // other may be increasing or decreasing
    Set( other.Min(), other.Max() );
    rc = true;
  }
  else {
    double a, b, mn, mx;
    a = Min();
    b = other.Min();
    mn = (a<=b) ? a : b;
    a = Max();
    b = other.Max();
    mx = (a>=b) ? a : b;
    if ( mn <= mx ) {
      Set(mn,mx);
      rc = true;
    }
    else
      Destroy();
  }
  return rc;
}

//////////
  // The union of an empty set and an increasing interval is the increasing
  // interval.  The union of two empty sets is empty. The union of an empty
  // set an a non-empty interval is the non-empty interval.
  // The union of two non-empty intervals is
// union = [min(argA.Min(),argB.Min()), max(argA.Max(),argB.Max()),]
// Union() returns true if the union is not empty.
bool MnjInterval::Union( // this = union of two args
       const MnjInterval& ain, 
       const MnjInterval& bin
       )
{
  bool rc = false;
  if ( bin.IsEmptySet() ) {
    // ain may be increasing, decreasing, or empty
    Set( ain.Min(), ain.Max() );
    rc = !IsEmptySet();
  }
  else if ( ain.IsEmptySet() ) {
    // bin may be increasing or decreasing
    Set( bin.Min(), bin.Max() );
    rc = true;
  }
  else {
    double a, b, mn, mx;
    a = ain.Min();
    b = bin.Min();
    mn = (a<=b) ? a : b;
    a = ain.Max();
    b = bin.Max();
    mx = (a>=b) ? a : b;
    if ( mn <= mx ) {
      Set(mn,mx);
      rc = true;
    }
    else
      Destroy();
  }
  return rc;
}
