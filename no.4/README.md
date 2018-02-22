## 지상으로부터 전송된 메시지

니어스랩에서는 지상에서 드론으로 메시지를 보낼 때, 외부인들이 알아볼 수 없도록 암호화를 하기로 했다.

드론으로 가는 메시지는 알파벳 대문자로 이루어진 명령문인데, 이것에 알파벳 소문자를 붙여서 알기 어렵게 하는 아이디어를 냈다.

드론으로 가는 메시지는 다음과 같다.

```
START
STOP
GO LEFT
GO RIGHT
```

암호는 다음과 같은 규칙이 있다.
```
(규칙 1) 단어를 선택하여 글자 사이에 같은 알파벳 소문자를 넣는다. ex) START -> SaTaAaRaT
(규칙 2) 단어를 선택하여 단어 앞뒤에 같은 알파벳 소문자를 넣는다. ex) STOP -> bSTOPb
위의 두 가지 규칙은 한 단어당 한번만 적용될 수 있다.
한번 쓰인 알파벳 소문자는 다시 쓰일 수 없다.
```

위의 규칙에 따라서 GO LEFT는 다음처럼 변환될 수 있다.
```
aGOabLEFTb
aGOaLbEbFbT
GaObLEFTb
GaOLbEbFbT
```

지상으로 부터의 입력은 다음과 같은 문자열이 주어진다.
```
GaObLEFTb
cGOcRdIdGdHdT
```

위의 문자열을 받아서 드론이 움직일 수 있도록 원래의 커맨드를 찾아라.

전송된 문자열 | 진짜 메시지
------------ | -------------
kSTARTk | START
SiTiOiP | STOP
GaObLEFTb | GO LEFT
cGOcRdIdGdHdT | GO RIGHT


시작 코드)

```cpp
#include <string>

using namespace std;

string solution(string sentence) {
    string answer = "";
    return answer;
}
```
