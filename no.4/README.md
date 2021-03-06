## 네번째 문제 : 드론이 찍어온 지도

니어스랩에서 제주도에 드론을 날려보니 다음과 같은 지도 데이터를 가져왔다.
```
[
  [1, 1, 1, 0], 
  [1, 2, 2, 0], 
  [1, 0, 0, 1],
  [0, 0, 0, 1],
  [0, 0, 0, 3],
  [0, 0, 0, 3]
]
```
지도에서 같은 종류의 숫자가 상하좌우로 연결되어 있으면, 하나의 영역으로 생각한다.

지도에서 0은 아무것도 없음을 의미하고, 1은 밭, 2는 풍력발전기, 3은 주택을 의미한다.

회사에서는 위의 지도를 읽어서 다음과 같은 정보를 얻고 싶다.

```
Q) 지도를 몇 개의 영역으로 나눌 수 있는가?
A) 좌측 상단의 밭(1) 영역, 중앙에 풍력발전기(2) 영역, 우측 중단에 밭(1) 영역, 우측 하단에 주택(3) 영역 총 4개의 영역으로 나눌 수 있다.
```

```
Q) 지도에서 가장 큰 영역의 크기는 무엇인가?
A) 좌측 상단의 밭(1) 영역이 Size = 5로 가장 크다.
```

Map을 입력 받아 위의 두 결과를 내는 프로그램을 만드시오. 

### 입력

별도로 콘솔에서 받는 입력은 없고, 아래의 2d-Array를 선언하여 작성하세요.
```
[
  [1, 1, 1, 0],
  [1, 2, 2, 0],
  [1, 0, 0, 1],
  [0, 0, 0, 1],
  [0, 0, 0, 3],
  [0, 0, 0, 3]
]
```

### 출력

지도의 영역 수, 가장 큰 영역의 크기
```
4, 5
```
