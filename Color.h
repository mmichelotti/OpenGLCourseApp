struct Color {
public:
    float r, g, b, a;

    Color();
    Color(float r, float g, float b, float a);

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color White;
    static const Color Black;

private:

    float saturate(float value) const;
};