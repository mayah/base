#include "base/containers/static_vector.h"

#include <gtest/gtest.h>

namespace {

class Destructable {
public:
    Destructable() = delete;
    explicit Destructable(int x, int y) : x_(x), y_(y) {}

    ~Destructable() { dtor_counter++; }

    static int dtor_counter;
private:

    int x_;
    int y_;
};

// static
int Destructable::dtor_counter = 0;

} // namespace anonymous

TEST(StaticVectorTest, basic)
{
    base::StaticVector<int, 10> st;
    EXPECT_EQ(0UL, st.size());

    for (int i = 0; i < 10; ++i) {
        st.push_back(i);
    }

    EXPECT_EQ(10UL, st.size());
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(i, st[i]);
    }
}

TEST(StaticVectorTest, destructable)
{
    EXPECT_EQ(0, Destructable::dtor_counter);

    int count = 0;
    {
        base::StaticVector<Destructable, 10> st;
        st.push_back(Destructable(1, 1));
        st.push_back(Destructable(1, 2));
        st.push_back(Destructable(1, 3));

        count = Destructable::dtor_counter;

        st.pop_back();
        EXPECT_EQ(count + 1, Destructable::dtor_counter);

        count = Destructable::dtor_counter;
    }

    // here, 2 Destructable should be destructed.
    EXPECT_EQ(count + 2, Destructable::dtor_counter);
}

TEST(StaticVectorTest, range_for)
{
    base::StaticVector<Destructable, 10> st;
    st.push_back(Destructable(1, 1));
    st.push_back(Destructable(2, 2));
    st.push_back(Destructable(3, 3));

    std::vector<Destructable> vs;
    for (const auto& s : st) {
        vs.push_back(s);
    }

    EXPECT_EQ(3UL, vs.size());
}
