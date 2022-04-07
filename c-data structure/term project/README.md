>黑白棋

- 資料結構期末專案(2021.1.12)
  - 組員: 陳育綺、朱曼華、王郁文、謝旻臻、蔡昀芳、許映婷、丁海倫
  - 指導教授: 李偉柏 教授
- 遊戲規則
  - 以鍵盤上下左右鍵控制落子位置，空白鍵落子。
  - 棋盤共有8行8列共64格。開局時，棋盤正中央的4格先置放黑白相隔的4枚棋子。只要落子和棋盤上任一枚己方的棋子在一條線上(橫、直、斜線皆可)夾著對方棋子，就能將對方的這些棋子轉變為我己方。只能在有辦法夾住對方棋子的位置上下子，也就是說，如果在任一位置落子都不能夾住對手的任一顆棋子，就要轉手讓對手下子。當雙方皆不能下子時，遊戲結束，在棋盤上子多的一方勝。
- 功能介紹
  >1. 執行黑白棋規則
  >2. 三種玩家模式(Player vs Player/ Player vs AI/ AI vs AI)
  >3. 簡單/ 困難模式
  >4. 顯示目前將落子位置
  >5. 顯示可落子位置
  >6. 輸入/ 顯示玩家名字
  >7. 顯示遊戲秒數/ 回合數/ 黑白兩方棋盤上剩子
  >8. 美化音效/ 棋盤
  - 實際遊戲畫面
  ![image](https://user-images.githubusercontent.com/66419079/162145301-6b9532e9-ebba-467f-932c-374f329ee34a.png)
  ![image](https://user-images.githubusercontent.com/66419079/162145358-439f8ca0-88d0-4148-a83c-35484b9f2501.png)
  ![image](https://user-images.githubusercontent.com/66419079/162145408-4baa16be-87ac-4fc7-bf2e-0f6d150eb910.png)
- AI介紹
  - 簡單模式
  - 僅考慮何處下子能翻轉最多對方子
  ![image](https://user-images.githubusercontent.com/66419079/162145610-5f099aaa-2ecb-4631-94ea-d78233be67f4.png)
  - 困難模式
  - 增加權重表，當權重大於最大可翻轉對方子數量，以權重表優先
  ![image](https://user-images.githubusercontent.com/66419079/162145667-7631e6f4-0809-492e-8741-0408e97c2ce1.png)
  ![image](https://user-images.githubusercontent.com/66419079/162145711-9135b659-664a-49eb-b851-a7d3d5e3b4ca.png)
