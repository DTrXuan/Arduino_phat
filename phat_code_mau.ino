// Định nghĩa chân kết nối. có thể thay đổi tùy vào phần cứng
#define cambien_i   8
#define bangtai_o   5
#define bom_o       6

// Định nghĩa giá trị thay thế cho trạng thái cảm biến.
#define KHONG_DOI    0
#define XUNG_LEN     1
#define XUNG_XUONG   2

// khai báo biến lưu trạng thái cảm biến
int cambien_st   = KHONG_DOI;
bool cambien_cur  = false;
bool cambien_last = false;

void setup() {

  /*Cảm biến
      Kết nối chân output của cảm biến với 1 chân digital của arduno
      ví dụ với chân D8
  */
  pinMode(cambien_i,INPUT_PULLUP); // Cấu hình chân D8 đọc cảm biến

  /*Động cơ băng tải
      Kết nối chân in của driver điều khiển động cơ với chân 5 (pwm)
  */
  pinMode(bangtai_o,OUTPUT);  // Cấu hình chân 5 output cấp xung điều khiển driver động cơ băng tải
  analogWrite(bangtai_o,200);  // Xuất xung pwm với duty = (200)*0.255%. Duty càng lớn tốc độ càng nhanh. range: 0 -> 255

  /*Động cơ bơm
      Kết nối chân in của driver điều khiển động cơ với chân 6 (pwm)
  */
  pinMode(bom_o,OUTPUT);  // Cấu hình chân 5 output cấp xung điều khiển driver động cơ bơm
  analogWrite(bangtai_o,0);  // Xuất xung pwm với duty = (0)*0.255%. Duty càng lớn tốc độ càng nhanh. range: 0 -> 255

  cambien_cur = (bool)digitalRead(cambien_i); // Đọc trạng thái cảm biến
  cambien_last = (bool)digitalRead(cambien_i);
}

void loop() {
  
  cambien_cur = (bool)digitalRead(cambien_i);

  /* Đọc và xử lý tín hiệu cảm biến */
  if (cambien_cur == false & cambien_last == true)
  {
      cambien_st = XUNG_LEN;
      cambien_last = cambien_cur;
  }
  else if (cambien_cur == true & cambien_last == false)
  {
      cambien_st = XUNG_XUONG;
      cambien_last = cambien_cur;
  }
  else
  {
      cambien_st = KHONG_DOI;
  }

  // phát hiện xung cạnh lên của cảm biến. giả sử cảm biến phát hiện vật trả về true, không trả về false.
  if (cambien_st == XUNG_LEN)
  {
      analogWrite(bangtai_o,0); // Dừng băng tải.
      analogWrite(bom_o,200); // bật đông cơ bơm. thay đổi số 200 để điều chỉnh tốc độ động cơ bơm
      delay(2000); // chờ 2000ms (2s).
      analogWrite(bom_o,0); // tắt động cơ bơm.
      delay(100); // chờ 100ms để đảm bảo nước trong vòi chảy hết mới chạy băng tải.
      analogWrite(bangtai_o,200); // cho băng tải chạy lại
  }
}