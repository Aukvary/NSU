#set page(paper: "a4", margin: 2cm)
#set text(font: "Linux Libertine", size: 11pt, lang: "ru")

#align(center, text(16pt, weight: "bold")[Лабораторная работа])
#align(center, [Выполнил: Долгих Алексей 25945])

== Дано
1. $s_1 = sigma(x_1)$, $s_2 = sigma(x_2)$
2. $o_(max) = max(s_1, s_2)$, $o_(min) = min(s_1, s_2)$
3. $y = o_(max) + o_(min)$

== Решение
$ 1. frac(partial E, partial o_(max)) = frac(partial E, partial y) dot frac(partial y, partial o_(max)) = frac(partial E, partial y) dot frac(partial (o_(max) + o_(min)), partial o_(max)) = frac(partial E, partial y) $
$ 2. frac(partial E, partial o_(min)) = frac(partial E, partial y) dot frac(partial y, partial o_(min)) = frac(partial E, partial y) dot frac(partial (o_(max) + o_(min)), partial o_(min)) = frac(partial E, partial y) $
$ 3. frac(partial y, partial s_1) = frac(partial (o_max + o_min), partial s_1) = frac(partial (s_1 + s_2), partial s_1) = 1 $
$ 4. frac(partial y, partial s_2) = frac(partial (o_max + o_min), partial s_2) = frac(partial (s_1 + s_2), partial s_1) = 1 $
$ 5. frac(partial s_1, partial x_1) = s_1 dot (1 - s_1) $

=== ответ
$ frac(partial E, partial x_1) = frac(partial E, partial y) dot frac(partial y, partial s_1) dot frac(partial s_1, partial x_1) = frac(partial E, partial y) dot (s_1 - s_1^2) $
$ frac(partial E, partial x_2) = frac(partial E, partial y) dot frac(partial y, partial s_2) dot frac(partial s_2, partial x_2) = frac(partial E, partial y) dot (s_2 - s_2^2) $