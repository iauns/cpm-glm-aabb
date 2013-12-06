/// \author James Hughes
/// \date   November 2013

#include <glm-aabb/AABB.hpp>
#include <gtest/gtest.h>

namespace {

// We want to use a macro so we know on what line the failure occurs.
#define vec3Test(A, B) \
{ \
  EXPECT_FLOAT_EQ((A).x, (B).x); \
  EXPECT_FLOAT_EQ((A).y, (B).y); \
  EXPECT_FLOAT_EQ((A).z, (B).z); \
}

TEST(AABB, Constructors)
{
  CPM_AABB_NS::AABB aabbNull;
  EXPECT_EQ(true, aabbNull.isNull());

  CPM_AABB_NS::AABB aabbSphere(glm::vec3(3.0), 1.0);
  EXPECT_EQ(false, aabbSphere.isNull());
  vec3Test(glm::vec3(2.0, 2.0, 2.0), aabbSphere.getMin());
  vec3Test(glm::vec3(4.0, 4.0, 4.0), aabbSphere.getMax());

  CPM_AABB_NS::AABB aabbMinMax(glm::vec3(0.0), glm::vec3(-1.0, 1.0, 3.0));
  EXPECT_EQ(false, aabbMinMax.isNull());
  vec3Test(glm::vec3(-1.0, 0.0, 0.0), aabbMinMax.getMin());
  vec3Test(glm::vec3( 0.0, 1.0, 3.0), aabbMinMax.getMax());

  CPM_AABB_NS::AABB aabbCopy(aabbSphere);
  EXPECT_EQ(false, aabbCopy.isNull());
  vec3Test(glm::vec3(2.0, 2.0, 2.0), aabbCopy.getMin());
  vec3Test(glm::vec3(4.0, 4.0, 4.0), aabbCopy.getMax());
}

TEST(AABB, MakeNonNull)
{
  CPM_AABB_NS::AABB aabb;  
  CPM_AABB_NS::AABB temp;  

  EXPECT_EQ(true, aabb.isNull());

  // Function to check to make sure aabb is NOT null, then set it to NULL.
  auto checkSetAABBNull = [](CPM_AABB_NS::AABB& check)
  {
    EXPECT_EQ(false, check.isNull());
    check.setNull();
    EXPECT_EQ(true, check.isNull());
  };

  // This case should NOT make the AABB valid. We don't have a valid AABB
  // with which to extend.
  aabb.extend(0.3);
  EXPECT_EQ(true, aabb.isNull());

  aabb.extend(glm::vec3(1.0));
  checkSetAABBNull(aabb);

  aabb.extend(glm::vec3(1.0), 0.5);
  checkSetAABBNull(aabb);

  temp.extend(glm::vec3(2.0), 0.5);
  aabb.extend(temp);
  checkSetAABBNull(aabb);
  checkSetAABBNull(temp);

  aabb.extendDisk(glm::vec3(1.0), glm::vec3(1.0, 0.0, 0.0), 0.5);
  checkSetAABBNull(aabb);

  aabb.translate(glm::vec3(999.0));
  EXPECT_EQ(true, aabb.isNull());

  aabb.scale(glm::vec3(3.0, 3.0, 3.0), glm::vec3(2.0));
  EXPECT_EQ(true, aabb.isNull());
}


TEST(AABB, ExtendNumericTests)
{
  CPM_AABB_NS::AABB aabb;

  vec3Test(glm::vec3(0.0), aabb.getDiagonal());

  aabb.extend(glm::vec3(1.0));
  EXPECT_EQ(false, aabb.isNull());
  vec3Test(glm::vec3(1.0, 1.0, 1.0), aabb.getMin());
  vec3Test(glm::vec3(1.0, 1.0, 1.0), aabb.getMax());

  aabb.extend(1.0);
  vec3Test(glm::vec3(0.0, 0.0, 0.0), aabb.getMin());
  vec3Test(glm::vec3(2.0, 2.0, 2.0), aabb.getMax());

  aabb.extend(glm::vec3(-4.0, 3.0, 1.0));
  vec3Test(glm::vec3(-4.0, 0.0, 0.0), aabb.getMin());
  vec3Test(glm::vec3( 2.0, 3.0, 2.0), aabb.getMax());
  EXPECT_FLOAT_EQ(6.0, aabb.getLongestEdge());
  EXPECT_FLOAT_EQ(2.0, aabb.getShortestEdge());

  // Sphere
  aabb.setNull();
  EXPECT_EQ(true, aabb.isNull());
  aabb.extend(glm::vec3(3.0), 1.0);
  EXPECT_EQ(false, aabb.isNull());
  vec3Test(glm::vec3(2.0, 2.0, 2.0), aabb.getMin());
  vec3Test(glm::vec3(4.0, 4.0, 4.0), aabb.getMax());
  vec3Test(aabb.getMax() - aabb.getMin(), aabb.getDiagonal());

  aabb.extend(0.5);
  vec3Test(glm::vec3(1.5, 1.5, 1.5), aabb.getMin());
  vec3Test(glm::vec3(4.5, 4.5, 4.5), aabb.getMax());
  vec3Test(aabb.getMax() - aabb.getMin(), aabb.getDiagonal());

  aabb.translate(glm::vec3(0.5));
  vec3Test(glm::vec3(2.0, 2.0, 2.0), aabb.getMin());
  vec3Test(glm::vec3(5.0, 5.0, 5.0), aabb.getMax());
  vec3Test(aabb.getMax() - aabb.getMin(), aabb.getDiagonal());
  
  aabb.setNull();
  EXPECT_EQ(true, aabb.isNull());

  aabb.extend(glm::vec3(1.0));
  aabb.extend(1.0);
  vec3Test(glm::vec3(0.0, 0.0, 0.0), aabb.getMin());
  vec3Test(glm::vec3(2.0, 2.0, 2.0), aabb.getMax());

  aabb.scale(glm::vec3(2.0), glm::vec3(1.0));
  vec3Test(glm::vec3(-1.0, -1.0, -1.0), aabb.getMin());
  vec3Test(glm::vec3( 3.0,  3.0,  3.0), aabb.getMax());

  aabb.setNull();
  aabb.extend(glm::vec3(1.0));
  aabb.extend(1.0);
  vec3Test(glm::vec3(0.0, 0.0, 0.0), aabb.getMin());
  vec3Test(glm::vec3(2.0, 2.0, 2.0), aabb.getMax());

  aabb.scale(glm::vec3(2.0), glm::vec3(0.0));
  vec3Test(glm::vec3(0.0, 0.0, 0.0), aabb.getMin());
  vec3Test(glm::vec3(4.0, 4.0, 4.0), aabb.getMax());
}

TEST(AABB, Itersect)
{
  CPM_AABB_NS::AABB bb1;
  bb1.extend(glm::vec3(1.0));
  bb1.extend(1.0);
  vec3Test(glm::vec3(0.0, 0.0, 0.0), bb1.getMin());
  vec3Test(glm::vec3(2.0, 2.0, 2.0), bb1.getMax());

  CPM_AABB_NS::AABB bb2;
  bb2.extend(glm::vec3(5.0));
  bb2.extend(1.0);
  vec3Test(glm::vec3(4.0, 4.0, 4.0), bb2.getMin());
  vec3Test(glm::vec3(6.0, 6.0, 6.0), bb2.getMax());

  CPM_AABB_NS::AABB bb3;
  bb3.extend(glm::vec3(1.0, 1.0, 1.0));
  bb3.extend(glm::vec3(5.0, 5.0, 5.0));
  vec3Test(glm::vec3(1.0, 1.0, 1.0), bb3.getMin());
  vec3Test(glm::vec3(5.0, 5.0, 5.0), bb3.getMax());

  EXPECT_EQ(CPM_AABB_NS::AABB::OUTSIDE, bb1.intersect(bb2));
  EXPECT_EQ(CPM_AABB_NS::AABB::INTERSECT, bb1.intersect(bb3));
  EXPECT_EQ(CPM_AABB_NS::AABB::INTERSECT, bb2.intersect(bb3));

  EXPECT_EQ(CPM_AABB_NS::AABB::INSIDE, bb1.intersect(bb1));
  EXPECT_EQ(CPM_AABB_NS::AABB::INSIDE, bb2.intersect(bb2));
  EXPECT_EQ(CPM_AABB_NS::AABB::INSIDE, bb3.intersect(bb3));

  CPM_AABB_NS::AABB bb1_inside(glm::vec3(0.5), glm::vec3(1.5));
  EXPECT_EQ(CPM_AABB_NS::AABB::INSIDE, bb1.intersect(bb1_inside));
  EXPECT_EQ(CPM_AABB_NS::AABB::OUTSIDE, bb2.intersect(bb1_inside));
  EXPECT_EQ(CPM_AABB_NS::AABB::INTERSECT, bb3.intersect(bb1_inside));

  CPM_AABB_NS::AABB bb2_inside(glm::vec3(4.5), glm::vec3(5.5));
  EXPECT_EQ(CPM_AABB_NS::AABB::OUTSIDE, bb1.intersect(bb2_inside));
  EXPECT_EQ(CPM_AABB_NS::AABB::INSIDE, bb2.intersect(bb2_inside));
  EXPECT_EQ(CPM_AABB_NS::AABB::INTERSECT, bb3.intersect(bb2_inside));

  CPM_AABB_NS::AABB bb3_inside1(glm::vec3(1.5), glm::vec3(4.5));
  EXPECT_EQ(CPM_AABB_NS::AABB::INTERSECT, bb1.intersect(bb3_inside1));
  EXPECT_EQ(CPM_AABB_NS::AABB::INTERSECT, bb2.intersect(bb3_inside1));
  EXPECT_EQ(CPM_AABB_NS::AABB::INSIDE, bb3.intersect(bb3_inside1));

  CPM_AABB_NS::AABB bb3_inside2(glm::vec3(2.5), glm::vec3(3.5));
  EXPECT_EQ(CPM_AABB_NS::AABB::OUTSIDE, bb1.intersect(bb3_inside2));
  EXPECT_EQ(CPM_AABB_NS::AABB::OUTSIDE, bb2.intersect(bb3_inside2));
  EXPECT_EQ(CPM_AABB_NS::AABB::INSIDE, bb3.intersect(bb3_inside2));
}

}
