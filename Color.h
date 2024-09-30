class Color {
public:
    float r, g, b, a;

    Color();
    Color(float r, float g, float b, float a);

    static const Color red;
    static const Color green;
    static const Color blue;
    static const Color white;
    static const Color black;

private:

    float saturate(float value) const;
};