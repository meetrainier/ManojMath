#pragma once
#include "MnjInterval.h"
#include "MathConstant.h"
#include "MnjVector.h"
#include "MnjPlane.h"
class MnjPlane;

class  Mnj4x4Matrix
{
public:
  double m_xform[4][4]; // [i][j] = row i, column j.  I.e., 
                        //
                        //           [0][0] [0][1] [0][2] [0][3]
                        //           [1][0] [1][1] [1][2] [1][3]
                        //           [2][0] [2][1] [2][2] [2][3]
                        //           [3][0] [3][1] [3][2] [3][3]

  // use implicit destructor, copy constructor
  Mnj4x4Matrix(void);                     // zero matrix

  Mnj4x4Matrix( int );                // diagonal matrix (d,d,d,1)
  Mnj4x4Matrix( double );             // diagonal matrix (d,d,d,1)

 // Mnj4x4Matrix( double[4][4] );       // from standard double m[4][4]
  Mnj4x4Matrix( float[4][4] );        // from standard float m[4][4]
  Mnj4x4Matrix( const double m[4][4] );
  
  Mnj4x4Matrix( const double* );      // from array of 16 doubles (row0,row1,row2,row3)
  Mnj4x4Matrix( const float* );       // from array of 16 floats (row0,row1,row2,row3)
  
  //Mnj4x4Matrix( const ON_Matrix& ); // from upper left 4x4 of an
                                    // arbitrary matrix.  Any missing
                                    // rows/columns are set to identity. 
	Mnj4x4Matrix(const MnjPoint<double>& P,	// as a frame. 
						const MnjVector& X,	
						const MnjVector& Y,	
						const MnjVector& Z); 
    Mnj4x4Matrix( const MnjPoint<double>& P,
														 const MnjDirection& X,
														 const MnjDirection& Y,
														 const MnjDirection& Z);
    void Translation( const MnjPoint<double>& v );
  // use implicit operator=(const MnjVector&), operator==
  
  double* operator[](int);
  const double* operator[](int) const;

  // xform = scalar results in a diagonal 3x3 with bottom row = 0,0,0,1
  Mnj4x4Matrix& operator=( int );
  Mnj4x4Matrix& operator=( float );
  Mnj4x4Matrix& operator=( double );
 // Mnj4x4Matrix& operator=( const ON_Matrix& ); // from upper left 4x4 of an
                                               // arbitrary matrix.  Any missing
                                               // rows/columns are set to identity.

  // All non-commutative operations have "this" as left hand side and
  // argument as right hand side.
  //ON_2dPoint operator*( const ON_2dPoint& ) const;
  MnjPoint<double> operator*( const MnjPoint<double>& ) const;
  //ON_4dPoint operator*( const ON_4dPoint& ) const;
  
  //ON_2dVector operator*( const ON_2dVector& ) const;
  MnjVector operator*( const MnjVector& ) const;
  
  Mnj4x4Matrix operator*( const Mnj4x4Matrix& /*rhs*/ ) const;
  Mnj4x4Matrix operator+( const Mnj4x4Matrix& ) const;
  Mnj4x4Matrix operator-( const Mnj4x4Matrix& /*rhs*/ ) const;

  /*
  Description:
    Test the entries of the transformation matrix
    to see if they are valid number.
  Returns:
    True if IsValid() is true for every number
    in the transformation matrix.
  */
  bool IsValid() const;

  /*
  Returns:
    true if matrix is the identity transformation

          1 0 0 0
          0 1 0 0
          0 0 1 0
          0 0 0 1
  Remarks:
    The test for zero is fabs(x) <= zero_tolerance.
    The test for one is fabs(x-1) <= zero_tolerance.
  */
  bool IsIdentity( double zero_tolerance = 0.0) const;
  
  /*
  Returns:
    true if matrix is a pure translation

          1 0 0 dx
          0 1 0 dy
          0 0 1 dz
          0 0 0 1
  Remarks:
    The test for zero is fabs(x) <= zero_tolerance.
    The test for one is fabs(x-1) <= zero_tolerance.
  */
  bool IsTranslation( double zero_tolerance = 0.0) const;
  
  /*
  Returns:
    true if matrix is the zero transformation

          0 0 0 0
          0 0 0 0
          0 0 0 0
          0 0 0 *
  */
  bool IsZero() const;

  /*
  Description:
    A similarity transformation can be broken into a sequence
    of dialations, translations, rotations, and reflections.
  Returns:
    +1: This transformation is an orientation preserving similarity.
    -1: This transformation is an orientation reversing similarity.
     0: This transformation is not a similarity.
  */
  int IsSimilarity() const;


  int Compare( const Mnj4x4Matrix& other ) const;

  
  // matrix operations
  void Transpose(); // transposes 4x4 matrix

  int 
  Rank( // returns 0 to 4
    double* = NULL // If not NULL, returns minimum pivot
  ) const;

  double
  Determinant( // returns determinant of 4x4 matrix
    double* = NULL // If not NULL, returns minimum pivot
  ) const;

  bool
  Invert( // If matrix is non-singular, returns true,
          // otherwise returns false and sets matrix to 
          // pseudo inverse.
    double* = NULL // If not NULL, returns minimum pivot
  );

  Mnj4x4Matrix
  Inverse(  // If matrix is non-singular, returns inverse,
            // otherwise returns pseudo inverse.
    double* = NULL // If not NULL, returns minimum pivot
  ) const;

  /*
  Description:
    When transforming 3d point and surface or mesh normals
    two different transforms must be used.
    If P_xform transforms the point, then the inverse
    transpose of P_xform must be used to tranform normal
    vectors.
  Parameters:
    N_xform - [out]
  Returns:
    The determinant of the transformation.
    If non-zero, "this" is invertable and N_xform can be calculated.
    False if "this" is not invertable, in which case
    the returned N_xform = this with the right hand column
    and bottom row zeroed out.
  */
  double GetSurfaceNormalXform( Mnj4x4Matrix& N_xform ) const;

  /*
  Description:
    If a texture mapping is applied to an object, the object
    is subsequently transformed by T, and the texture mapping
    needs to be recalculated, then two transforms are required
    to recalcalculate the texture mapping.
  Parameters:
    P_xform - [out] 
      Transform to apply to points before applying the
      texture mapping transformation.
    N_xform - [out] 
      Transform to apply to surface normals before applying
      the texture mapping transformation.
  Returns:
    The determinant of the "this" transformation.
    If non-zero, "this" is invertable and P_xform and N_xform
    were calculated.
    False if "this" is not invertable, in which case
    the returned P_xform and N_xform are the identity.
  */
  double GetMappingXforms( Mnj4x4Matrix& P_xform, Mnj4x4Matrix& N_xform ) const;

  // Description:
  //   Computes matrix * transpose([x,y,z,w]).
  //
  // Parameters:
  //   x - [in]
  //   y - [in]
  //   z - [in]
  //   z - [in]
  //   ans - [out] = matrix * transpose([x,y,z,w])
  void ActOnLeft(
         double, // x
         double, // y
         double, // z
         double, // w
         double[4] // ans
         ) const;

  // Description:
  //   Computes [x,y,z,w] * matrix.
  //
  // Parameters:
  //   x - [in]
  //   y - [in]
  //   z - [in]
  //   z - [in]
  //   ans - [out] = [x,y,z,w] * matrix
  void ActOnRight(
         double, // x
         double, // y
         double, // z
         double, // w
         double[4] // ans
         ) const;

  ////////////////////////////////////////////////////////////////
  // standard transformations

  // All zeros including the bottom row.
  void Zero();

  // diagonal is (1,1,1,1)
  void Identity();

  // diagonal 3x3 with bottom row = 0,0,0,1
  void Diagonal(double); 

  /*
  Description:
    Create non-uniform scale transformation with the origin as
    a fixed point.
  Parameters:
    fixed_point - [in]
    x_scale_factor - [in]
    y_scale_factor - [in]
    z_scale_factor - [in]
  Remarks:
    The diagonal is (x_scale_factor, y_scale_factor, z_scale_factor, 1)
  */
  void Scale( 
    double x_scale_factor,
    double y_scale_factor,
    double z_scale_factor
    );

  /*
  Description:
    Create non-uniform scale transformation with the origin as
    a fixed point.
  Parameters:
    fixed_point - [in]
    scale_vector - [in]
  Remarks:
    The diagonal is (scale_vector.x, scale_vector.y, scale_vector.z, 1)
  */
  void Scale( 
    const MnjVector& scale_vector
    );

  /*
  Description:
    Create uniform scale transformation with a specified
    fixed point.
  Parameters:
    fixed_point - [in]
    scale_factor - [in]
  */
  void Scale
    (
    MnjPoint<double> fixed_point,
    double scale_factor
    );

  /*
  Description:
    Create non-uniform scale transformation with a specified
    fixed point.
  Parameters:
    plane - [in] plane.origin is the fixed point
    x_scale_factor - [in] plane.xaxis scale factor
    y_scale_factor - [in] plane.yaxis scale factor
    z_scale_factor - [in] plane.zaxis scale factor
  */
  void Scale
    (
    const MnjPlane& plane,
    double x_scale_factor,
    double y_scale_factor,
    double z_scale_factor
    );

  /*
  Description:
    Create shear transformation.
  Parameters:
    plane - [in] plane.origin is the fixed point
    x1 - [in] plane.xaxis scale factor
    y1 - [in] plane.yaxis scale factor
    z1 - [in] plane.zaxis scale factor
  */
  void Shear
    (
    const MnjPlane& plane,
    const MnjVector& x1,
    const MnjVector& y1,
    const MnjVector& z1
    );

  // Right column is (d.x, d.y,d.z, 1).
  void Translation( 
    const MnjVector& // d
    );

  // Right column is (dx, dy, dz, 1).
  void Translation( 
    double, // dx
    double, // dy
    double  // dz
    );

  // Description:
  //   Get transformation that projects to a plane
  // Parameters:
  //   plane - [in] plane to project to
  // Remarks:
  //   This transformaton maps a 3d point P to the
  //   point plane.ClosestPointTo(Q).
  void PlanarProjection(
    const MnjPlane& plane
    );

  // Description: 
  //   The Rotation() function is overloaded and provides several
  //   ways to compute a rotation transformation.  A positive
  //   rotation angle indicates a counter-clockwise (right hand rule)
  //   rotation about the axis of rotation.
  //
  // Parameters:
  //   sin_angle - sin(rotation angle)
  //   cos_angle - cos(rotation angle)
  //   rotation_axis - 3d unit axis of rotation
  //   rotation_center - 3d center of rotation
  //
  // Remarks: 
  //   In the overloads that take frames, the frames should 
  //   be right hand orthonormal frames 
  //   (unit vectors with Z = X x Y).  
  //   The resulting rotation fixes
  //   the origin (0,0,0), maps initial X to 
  //   final X, initial Y to final Y, and initial Z to final Z.
  //  
  //   In the overload that takes frames with center points, 
  //   if the initial and final center are equal, then that 
  //   center point is the fixed point of the rotation.  If 
  //   the initial and final point differ, then the resulting
  //   transform is the composition of a rotation fixing P0
  //   and translation from P0 to P1.  The resulting 
  //   transformation maps P0 to P1, P0+X0 to P1+X1, ...
  //
  //   The rotation transformations that map frames to frames
  //   are not the same as the change of basis transformations
  //   for those frames.  See Mnj4x4Matrix::ChangeBasis().
  //   
  void Rotation(
    double sin_angle,
    double cos_angle,
    MnjVector rotation_axis,
    MnjPoint<double> rotation_center
    );

  // Parameters:
  //   angle - rotation angle in radians
  //   rotation_axis - 3d unit axis of rotation
  //   rotation_center - 3d center of rotation
  void Rotation(
    double angle_radians,
    MnjVector rotation_axis,
    MnjPoint<double> rotation_center
    );

  /*
  Description:
    Calculate the minimal transformation that rotates
    start_dir to end_dir while fixing rotation_center.    
  */
  void Rotation(
    MnjVector start_dir,
    MnjVector end_dir,
    MnjPoint<double> rotation_center
    );

  // Parameters:
  //   X0 - initial frame X
  //   Y0 - initial frame Y
  //   Z0 - initial frame Z
  //   X1 - final frame X
  //   Y1 - final frame Y
  //   Z1 - final frame Z
  //
  void Rotation( 
    const MnjVector& X0,
    const MnjVector& Y0,
    const MnjVector& Z0,
    const MnjVector& X1,
    const MnjVector& Y1,
    const MnjVector& Z1
    );

  // Parameters:
  //   P0 - initial frame center
  //   X0 - initial frame X
  //   Y0 - initial frame Y
  //   Z0 - initial frame Z
  //   P1 - initial frame center
  //   X1 - final frame X
  //   Y1 - final frame Y
  //   Z1 - final frame Z
  void Rotation( 
    const MnjPoint<double>& P0,
    const MnjVector& X0,
    const MnjVector& Y0,
    const MnjVector& Z0,
    const MnjPoint<double>& P1,
    const MnjVector& X1,
    const MnjVector& Y1,
    const MnjVector& Z1
    );

  /*
  Description:
    Create rotation transformation that maps plane0 to plane1.
  Parameters:
    plane0 - [in]
    plane1 - [in]
  */
  void Rotation( 
    const MnjPlane& plane0,
    const MnjPlane& plane1
    );

  /*
  Description:
    Create mirror transformation matrix.
  Parameters:
    point_on_mirror_plane - [in] point on mirror plane
    normal_to_mirror_plane - [in] normal to mirror plane
  Remarks:
    The mirror transform maps a point Q to
    Q - (2*(Q-P)oN)*N, where
    P = point_on_mirror_plane and N = normal_to_mirror_plane.
  */
  void Mirror(
    MnjPoint<double> point_on_mirror_plane,
    MnjVector normal_to_mirror_plane
    );



  // Description:
  //   Get a change of basis transformation.
  // Parameters:
  //   X0 - initial basis X (X0,Y0,Z0 can be any 3d basis)
  //   Y0 - initial basis Y
  //   Z0 - initial basis Z
  //   X1 - final basis X (X1,Y1,Z1 can be any 3d basis)
  //   Y1 - final basis Y
  //   Z1 - final basis Z
  // Remarks:
  //   Change of basis transformations and rotation transformations
  //   are often confused.  This is a change of basis transformation.
  //   If Q = a0*X0 + b0*Y0 + c0*Z0 = a1*X1 + b1*Y1 + c1*Z1
  //   then this transform will map the point (a0,b0,c0) to (a1,b1,c1)
  bool ChangeBasis( 
    const MnjVector& X0,
    const MnjVector& Y0,
    const MnjVector& Z0,
    const MnjVector& X1,
    const MnjVector& Y1,
    const MnjVector& Z1
    );

  // Parameters:
  //   P0 - initial center
  //   X0 - initial basis X (X0,Y0,Z0 can be any 3d basis)
  //   Y0 - initial basis Y
  //   Z0 - initial basis Z
  //   P1 - final center
  //   X1 - final basis X (X1,Y1,Z1 can be any 3d basis)
  //   Y1 - final basis Y
  //   Z1 - final basis Z
  // Remarks:
  //   Change of basis transformations and rotation transformations
  //   are often confused.  This is a change of basis transformation.
  //   If Q = P0 + a0*X0 + b0*Y0 + c0*Z0 = P1 + a1*X1 + b1*Y1 + c1*Z1
  //   then this transform will map the point (a0,b0,c0) to (a1,b1,c1)
  bool ChangeBasis( 
    const MnjPoint<double>& P0,
    const MnjVector& X0,
    const MnjVector& Y0,
    const MnjVector& Z0,
    const MnjPoint<double>& P1,
    const MnjVector& X1,
    const MnjVector& Y1,
    const MnjVector& Z1
    );

  // standard viewing transformations
  void WorldToCamera( 
         const MnjPoint<double>&,  // CameraLocation
         const MnjVector&, // unit CameraX vector (right)
         const MnjVector&, // unit CameraY vector (up)
         const MnjVector&  // unit CameraZ vector (from screen to camera)
         );
  void CameraToWorld( 
         const MnjPoint<double>&,  // CameraLocation
         const MnjVector&, // unit CameraX vector (right)
         const MnjVector&, // unit CameraY vector (up)
         const MnjVector&  // unit CameraZ vector (from screen to camera)
         );
  bool CameraToClip( // maps viewport frustum to -1 <= x,y,z <= 1 box
      bool, // true for perspective, false for orthographic
      double, double, // left != right (usually left < right )
      double, double, // bottom != top (usually bottom < top )
      double, double  // near != far (usually 0 < near < far )
      );

  // maps -1 <= x,y,z <= 1 box to viewport frustum
  bool ClipToCamera( 
      int, // true for perspective, false for orthographic
      double, double, // left != right (usually left < right )
      double, double, // bottom != top (usually bottom < top )
      double, double  // near != far an bot are non-zero (usually 0 < near < far )
      );

  // Computes transform that maps the clipping box 
  //
  //           -1<x<1,-1<y<1,-1<z<1 
  //
  // to the screen box
  //
  //          (left,right) X (bottom,top) X (near,far)
  bool ClipToScreen(                           
      double, // left
      double, // right
      double, // bottom
      double, // top
      double, // near_z
      double  // far_z
      );

  // Computes transform that maps the screen box
  //
  //          (left,right) X (bottom,top) X (near,far)
  //  
  // to the clipping box 
  //
  //           -1<x<1,-1<y<1,-1<z<1 
  bool ScreenToClip(
      double, // left
      double, // right
      double, // bottom
      double, // top
      double, // near_z
      double  // far_z
      );

  // Description: Computes homogeneous point clipping flags and
  //   returns an int with bits set to indicate if the point
  //   is outside of the clipping box.
  //
  // Parameters:
  //   point - [in] 4d homogeneous clipping coordinate point
  //
  // Returns:  
  //  @table  
  //   bit      point location
  //   1        x/w < -1
  //   2        x/w > +1
  //   4        y/w < -1
  //   8        y/w > +1
  //   16       z/w < -1
  //   32       z/w > +1
  //
  int ClipFlag4d(
    const double* // point
    ) const;

  // Parameters:
  //   count - [in] number of 4d points
  //   stride - [in] (>=4)
  //   points - [in] 4d clipping coordinate points 
  //            (array of stride*count doubles)
  //   bTestZ - [in] (default=true) if false, do not test "z" coordinate
  //
  int ClipFlag4d(
    int, // count
    int, // stride
    const double*, // points
    bool = true // bTeztZ
    ) const;

  // Description: 
  //   Computes 3d point clipping flags and
  //   returns an int with bits set to indicate if the point
  //   is outside of the clipping box.
  //
  // Parameters:
  //   point - [in] 3d clipping coordinate point
  //
  // Returns:  
  //  @table  
  //   bit      point location
  //   1        x < -1
  //   2        x > +1
  //   4        y < -1
  //   8        y > +1
  //   16       z < -1
  //   32       z > +1
  int ClipFlag3d(
    const double* // point
    ) const;

  // Parameters:
  //   count - [in] number of 3d points
  //   stride - [in] (>=3)
  //   points - [in] 3d clipping coordinate points (array of stride*count doubles)
  //   bTestZ - [in] (default=true) if false, do not test "z" coordinate
  //
  int ClipFlag3d(
    int, // count
    int, // stride 
    const double*, // points
    bool = true // bTestZ//mnj
    ) const;

  // Description: Computes 3d clipping flags for a 3d bounding
  //   box and returns an int with bits set to indicate if
  //   the bounding box is outside of the clipping box.
  //
  // Parameters:
  //   boxmin - [in] 3d boxmin corner
  //   boxmax - [in] 3d boxmax corner
  //
  // Returns:  
  //  @table  
  //   bit      box location
  //   1        boxmax x < -1
  //   2        boxmin x > +1
  //   4        boxmax y < -1
  //   8        boxmin y > +1
  //   16       boxmax z < -1
  //   32       boxmin z > +1
  int ClipFlag3dBox(
    const double*, // boxmin
    const double*  // boxmax
    ) const;


  /*
  Description:
    Calculates the transformation that linearly maps
    old_interval to new_interval.
  Parameters:
    dir - [in] 0 = x, 1 = y, 2= z;
    old_interval - [in]
    new_interval - [in]
  */
  bool IntervalChange(
    int dir,
    MnjInterval old_interval,
    MnjInterval new_interval
    );

  	
  bool ChangeBasis( 
  const MnjPlane& plane0, // initial plane
  const MnjPlane& plane1  // final plane
  );
  
	
};


