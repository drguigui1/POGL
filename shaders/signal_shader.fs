#version 460 core

out vec4 FragColor;

in vec3 fColor;
in vec2 fTexCoord;

uniform sampler2D texture1;
uniform float vTime;

float speed = 3.0;
float rate = 15.0;

float get_signal() {
  float x = speed * vTime + rate * (-1.0 + 2.0 * fTexCoord.x);
  float base = (1.0 + cos(x * 2.5 + vTime)) * (1.0 + sin(x * 3.5 + vTime));
  float z = fract(0.1 * x);
  z = pow(max(z, 1.0 - z), 20.0);
  float pulse = exp(-10000.0 * z);
  return pow(clamp(1.0 - abs((-1.0 + 2.0 * fTexCoord.y) - (base * 0.1 + pulse-0.5)), 0.0, 1.0), 20.0);
}

vec3 get_wave() {
  vec3 wave;
  vec2 uv  = -1.25 + 2.5 * fTexCoord;
  for (float i = 0.0; i < 15.0; i++) {
      uv.y += 0.5 * sin(uv.x + i/1.5 + vTime);
      float width = 1.0 / (150.0 * abs(uv.y));
      wave += vec3(width * 1.7 * sin(vTime - 1.5), width, width * 1.5 * sin(vTime + 1));
  }

  return wave;
}

void main(void)
{
  float signal = get_signal();

  if (signal <= 0.5)
      discard;

  vec3 wave = get_wave();

  FragColor = signal * vec4(wave * 0.5 + fColor * 0.8, 1.0);
}
