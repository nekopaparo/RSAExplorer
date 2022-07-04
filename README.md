# RSAExplorer

## RSA (Rivest–Shamir–Adleman)

#### 密鑰生成
1. 選擇2個質數(p, q)，且p != q
2. N = pq;
3. r = 最小公倍數(p - 1, q - 1)
4. e = 選擇一個數和r互質
5. d * e % r == 1，算出d
6. 公鑰 = {N, e}, 私鑰 = {N, d}

#### 加密
* message ^ e ≡ enmessage (mod N)
* enmessage = (message ^ e) % N

#### 解密
* enmessage ^ d ≡ message (mod N)
* message = (enmessage ^ d) % N

## 展示
* 不支援中文加密

### 基本
![基本](https://lh3.googleusercontent.com/TyyA2GJaEVh_2hEqos-98rKcTUZ1a3m_xovzYXPu-SsmbsQCtnhDAQhfHIwMzewmgXbs2Uz225BUVo3vXV7jzR_cv_UF902WYrfkOP8i6kxG_9Gc6_5dZddXkAwTXOf8hkqYXg73OQ=w2400)

### 解碼
![解碼](https://lh3.googleusercontent.com/rOckk-KqDECDBd45_oxVboee2ZFD4HWbeyjrg4iscLzpmSSjUmmmYRIghIWzfruDV1PWbq3EFGSfE8Tm2qlGjLbuhondeblW8XJkaDAwaDwzqsEtYDKt-beKTpLDMV7tTDdYVfxj5g=w2400)