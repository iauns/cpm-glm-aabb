/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2013 James Hughes.


   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

/// \author James Hughes
/// \date   December 2013

#ifndef IAUNS_GLM_AABB_HPP
#define IAUNS_GLM_AABB_HPP

#include <glm/glm.hpp>

namespace CPM_GLM_AABB_NS {

/// Axis aligned bounding box implemented on top of GLM.
class AABB
{
public:
  /// Builds a null AABB.
  AABB();

  /// Builds an AABB that encompasses a sphere of \p radius and \p center.
  AABB(const glm::vec3& center, glm::float_t radius);

  /// Builds an AABB that contains the two points.
  AABB(const glm::vec3& p1, const glm::vec3& p2);

  /// Copy constructor.
  AABB(const AABB& aabb);

  ~AABB();

  /// Set the AABB as NULL (not set).
  void setNull()      {mMin = glm::vec3(1.0); mMax = glm::vec3(1.0);}

  /// Returns true if AABB is NULL (not set).
  void isNull() const {return mMin.x > mMax.x || mMin.y > mMax.y || mMin.z > mMax.z;}

  /// Extend the bounding box on all sides by \p val.
  void extend(glm::float_t val);

  /// Expand the AABB to include point \p p.
  void extend(const glm::vec3& p);

  /// Expand the AABB to include a sphere centered at \p p and of radius \p r.
  void extend(const glm::vec3& p, glm::float_t r);

  /// Expand the AABB to encompass the given AABB.
  void extend(const AABB& aabb);

  /// Expand the AABB to include a disk centered at \p c, with normal \p n,
  /// and radius \p r.
  /// \todo Untested -- This function is not represented in our unit tests.
  void extendDisk(const glm::vec3& c, const glm::vec3& n, glm::float_t r);

  /// Translates AABB by vector \p v.
  void translate(const glm::vec3& v);

  /// Scale the AABB by \p s, centered around \p o.
  void scale(const glm::vec3& s, const glm::vec3& o);

  /// Retrieves the diagonal vector (computed as mMax - mMin).
  /// If the AABB is NULL, then a vector of all zeros is returned.
  glm::vec3 getDiagonal() const;

  /// Retrieves the longest edge.
  /// If the AABB is NULL, then 0 is returned.
  glm::float_t getLongestEdge() const;

  /// Retrieves the shortest edge.
  /// If the AABB is NULL, then 0 is returned.
  glm::float_t getShortestEdge() const;

  /// Retrieves the AABB's minimum point.
  glm::vec3 getMin() const {return mMin;}

  /// Retrieves the AABB's maximum point.
  glm::vec3 getMax() const {return mMax;}

  /// Returns true if AABBs share a face overlap.
  /// \todo Untested -- This function is not represented in our unit tests.
  bool overlaps(const AABB& bb) const;

  enum INTERSECTION_TYPE { INSIDE, INTERSECT, OUTSIDE };
  /// Returns one of the intersection types. If either of the aabbs are invalid,
  /// then OUTSIDE is returned.
  INTERSECTION_TYPE intersect(const AABB& bb) const;

  /// Function from SCIRun. Here is a summary of SCIRun's description:
  /// Returns true if the two AABB's are similar. If diff is 1.0, the two
  /// bboxes have to have about 50% overlap each for x,y,z. If diff is 0.0,
  /// they have to have 100% overlap.
  /// If either of the two AABBs is NULL, then false is returned.
  /// \todo Untested -- This function is not represented in our unit tests.
  bool isSimilarTo(const AABB& b, glm::float_t diff = 0.5) const;

protected:

  glm::vec3 mMin;
  glm::vec3 mMax;
};

} // namespace CPM_GLM_AABB_NS 

#endif 
