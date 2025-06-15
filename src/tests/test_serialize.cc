#include "common/tt_test.h"
#include "common/tt_serialize.h"

struct Point2D {
    double x;
    double y;

    Point2D() = default;
    Point2D(double x, double y) : x(x), y(y) {}
};

struct TestPointCloud {
    std::vector<Point2D> points;
};

struct TestSerialize {
    int a;
    double b;
    std::string str;
    std::vector<Point2D> scans;
    std::vector<TestPointCloud> point_clouds;
    std::vector<std::vector<Point2D>> point_clouds_2d;
};

TEST(serialize, test) {
    // STEP 1: 构造结构体
    TestSerialize data = {
        .a = 0,
        .b = 0.0,
        .str = "test",
        .scans = {Point2D(1, 2), Point2D(3, 4)},
        .point_clouds = {{{Point2D(1, 2), Point2D(3, 4)}},
                         {{Point2D(5, 6), Point2D(7, 8)}}},
        .point_clouds_2d = {{{Point2D(1, 2), Point2D(3, 4)}},
                            {{Point2D(5, 6), Point2D(7, 8)}}}
    };

    // STEP 2: 序列化
    std::string serialized_data;
    Serialize(data.a, serialized_data);
    Serialize(data.b, serialized_data);
    Serialize(data.str, serialized_data);
    SerializeVector(data.scans, serialized_data);
    Serialize(data.point_clouds.size(), serialized_data);
    for (const auto& pc : data.point_clouds) {
        SerializeVector(pc.points, serialized_data);
    }
    SerializeVectorVector(data.point_clouds_2d, serialized_data);

    // STEP 3: 反序列化
    TestSerialize deserialized_data;
    std::string in = serialized_data;
    Deserialize(deserialized_data.a, in);
    Deserialize(deserialized_data.b, in);
    Deserialize(deserialized_data.str, in);
    DeserializeVector(deserialized_data.scans, in);
    size_t point_clouds_size;
    Deserialize(point_clouds_size, in);
    deserialized_data.point_clouds.resize(point_clouds_size);
    for (size_t i = 0; i < point_clouds_size; ++i) {
        DeserializeVector(deserialized_data.point_clouds[i].points, in);
    }
    DeserializeVectorVector(deserialized_data.point_clouds_2d, in);

    // STEP 4: 验证
    ASSERT_EQ(data.a, deserialized_data.a);
    ASSERT_EQ(data.b, deserialized_data.b);
    ASSERT_EQ(data.str, deserialized_data.str);
    ASSERT_EQ(data.scans.size(), deserialized_data.scans.size());
    for (size_t i = 0; i < data.scans.size(); ++i) {
        ASSERT_NEAR(data.scans[i].x, deserialized_data.scans[i].x, 1e-6);
        ASSERT_NEAR(data.scans[i].y, deserialized_data.scans[i].y, 1e-6);
    }
    ASSERT_EQ(data.point_clouds.size(), deserialized_data.point_clouds.size());
    for (size_t i = 0; i < data.point_clouds.size(); ++i) {
        ASSERT_EQ(data.point_clouds[i].points.size(), deserialized_data.point_clouds[i].points.size());
        for (size_t j = 0; j < data.point_clouds[i].points.size(); ++j) {
            ASSERT_NEAR(data.point_clouds[i].points[j].x, deserialized_data.point_clouds[i].points[j].x, 1e-6);
            ASSERT_NEAR(data.point_clouds[i].points[j].y, deserialized_data.point_clouds[i].points[j].y, 1e-6);
        }
    }
    ASSERT_EQ(data.point_clouds_2d.size(), deserialized_data.point_clouds_2d.size());
    for (size_t i = 0; i < data.point_clouds_2d.size(); ++i) {
        ASSERT_EQ(data.point_clouds_2d[i].size(), deserialized_data.point_clouds_2d[i].size());
        for (size_t j = 0; j < data.point_clouds_2d[i].size(); ++j) {
            ASSERT_NEAR(data.point_clouds_2d[i][j].x, deserialized_data.point_clouds_2d[i][j].x, 1e-6);
            ASSERT_NEAR(data.point_clouds_2d[i][j].y, deserialized_data.point_clouds_2d[i][j].y, 1e-6);
        }
    }
    ASSERT_TRUE(in.empty());
}
