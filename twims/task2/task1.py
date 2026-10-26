import math
import random
import re
from collections import Counter
from pathlib import Path

import matplotlib.pyplot as plt

SEED = 42
TRAIN_RATIO = 0.8

DATA_DIR = Path(__file__).parent / "data" / "enron_spam" / "extracted"
HAM_USERS = ("beck-s", "farmer-d", "kaminski-v", "kitchen-l", "lokay-m", "williams-w3")
SPAM_USERS = ("BG", "GP", "SH")

WORD_RE = re.compile(r"[a-zа-яё]+")

LABELS = ("spam", "ham")
LABEL_RU = {"spam": "спам", "ham": "не спам"}


def preprocess(text: str) -> set[str]:
    return set(WORD_RE.findall(text.lower()))


def email_body(path: Path) -> str:
    text = path.read_text(encoding="utf-8", errors="ignore")
    text = text.replace("\r\n", "\n")
    return text.partition("\n\n")[2]


def load_emails() -> list[tuple[str, str]]:
    emails: list[tuple[str, str]] = []
    for label, users in (("ham", HAM_USERS), ("spam", SPAM_USERS)):
        for user in users:
            for path in sorted((DATA_DIR / user).rglob("*")):
                if path.is_file():
                    emails.append((email_body(path), label))
    return emails


class NaiveBayesClassifier:
    def __init__(self) -> None:
        self.word_docs: dict[str, Counter] = {label: Counter() for label in LABELS}
        self.class_docs: dict[str, int] = {label: 0 for label in LABELS}

    def fit(self, emails: list[tuple[str, str]]) -> None:
        for text, label in emails:
            self.class_docs[label] += 1
            for word in preprocess(text):
                self.word_docs[label][word] += 1

    def log_word_prob(self, word: str, label: str) -> float:
        n = self.class_docs[label]
        return math.log((self.word_docs[label][word] + 1) / (n + 2))

    def log_class_prob(self, label: str) -> float:
        total = sum(self.class_docs.values())
        return math.log(self.class_docs[label] / total)

    def log_scores(self, text: str) -> dict[str, float]:
        words = preprocess(text)
        return {
            label: self.log_class_prob(label)
            + sum(self.log_word_prob(word, label) for word in words)
            for label in LABELS
        }

    def classify(self, text: str) -> str:
        scores = self.log_scores(text)
        return "spam" if scores["spam"] > scores["ham"] else "ham"


def split_train_test(
    emails: list[tuple[str, str]],
) -> tuple[list[tuple[str, str]], list[tuple[str, str]]]:
    shuffled = list(emails)
    random.seed(SEED)
    random.shuffle(shuffled)

    cut = int(len(shuffled) * TRAIN_RATIO)
    return shuffled[:cut], shuffled[cut:]


def metrics(y_true: list[str], y_pred: list[str]) -> dict[str, float]:
    tp = sum(1 for t, p in zip(y_true, y_pred) if t == "spam" and p == "spam")
    fp = sum(1 for t, p in zip(y_true, y_pred) if t == "ham" and p == "spam")
    tn = sum(1 for t, p in zip(y_true, y_pred) if t == "ham" and p == "ham")
    fn = sum(1 for t, p in zip(y_true, y_pred) if t == "spam" and p == "ham")

    return {
        "accuracy": (tp + tn) / len(y_true),
        "sensitivity": tp / (tp + fn),
        "specificity": tn / (tn + fp),
        "tp": tp,
        "fp": fp,
        "tn": tn,
        "fn": fn,
    }


def report(
    counts: Counter,
    test_emails: list[tuple[str, str]],
    y_pred: list[str],
    res: dict[str, float],
) -> None:
    n = sum(counts.values())

    print("Корпус Enron-Spam (AUEB)")
    print("-" * 44)
    print(f"Обычных писем (ham):  {counts['ham']:>6,}".replace(",", " "))
    print(f"Спамовых писем:       {counts['spam']:>6,}".replace(",", " "))
    print(f"Всего писем:          {n:>6,}".replace(",", " "))
    print(f"Обучение / тест:      {TRAIN_RATIO:.0%} / {1 - TRAIN_RATIO:.0%}")
    print(f"Приор P(спам):        {counts['spam'] / n:.4f}")
    print()

    print("Качество на тестовой части")
    print("-" * 44)
    print(f"Точность (accuracy):       {res['accuracy']:.4f}")
    print(f"Чувствительность (sensitivity):  {res['sensitivity']:.4f}")
    print(f"Специфичность (specificity):     {res['specificity']:.4f}")
    print()

    print("Матрица ошибок")
    print("-" * 44)
    print(f"{'':>16} | {'предсказан спам':>15} | {'предсказан не спам':>18}")
    print("-" * 44)
    print(f"{'спам':>16} | {res['tp']:>15} | {res['fn']:>18}")
    print(f"{'не спам':>16} | {res['fp']:>15} | {res['tn']:>18}")
    print()

    print("Примеры с тестовой выборки")
    print("-" * 44)
    shown = 0
    for (text, true), pred in zip(test_emails, y_pred):
        if shown >= 4:
            break
        words = sorted(preprocess(text))
        snippet = " ".join(words[:12])
        if len(words) > 12:
            snippet += " ..."
        mark = "OK " if pred == true else "ERR"
        print(
            f"[{mark}] истинное: {LABEL_RU[true]:<8} предсказано: {LABEL_RU[pred]:<8}"
        )
        print(f"       {snippet}")
        shown += 1


def plot_confusion(res: dict[str, float]) -> str:
    path = Path(__file__).parent / "task1_spam_confusion.png"

    fig, ax = plt.subplots(figsize=(9, 5.5))

    outcomes = [
        ("спам → спам\n(верно)", res["tp"], "#2ca02c"),
        ("спам → не спам\n(пропущен спам)", res["fn"], "#ff7f0e"),
        ("не спам → спам\n(ложная тревога)", res["fp"], "#d62728"),
        ("не спам → не спам\n(верно)", res["tn"], "#1f77b4"),
    ]

    ax.bar(
        range(len(outcomes)),
        [v for _, v, _ in outcomes],
        color=[c for _, _, c in outcomes],
    )
    for i, (_, v, _) in enumerate(outcomes):
        ax.text(i, v, f"{v:,}".replace(",", " "), ha="center", va="bottom", fontsize=10)

    ax.set_xticks(range(len(outcomes)))
    ax.set_xticklabels([name for name, _, _ in outcomes], fontsize=9)
    ax.set_ylabel("Число писем")
    ax.set_title("Матрица ошибок наивного байесовского классификатора (тест)")
    ax.grid(axis="y", alpha=0.3)

    fig.tight_layout()
    fig.savefig(path, dpi=150)
    plt.close(fig)
    return str(path)


def main() -> None:
    emails = load_emails()
    counts = Counter(label for _, label in emails)

    train, test = split_train_test(emails)
    print(
        f"Писем: {len(emails):,}".replace(",", " ")
        + f"  (обучение: {len(train):,}, тест: {len(test):,})".replace(",", " ")
    )

    model = NaiveBayesClassifier()
    model.fit(train)

    y_true = [label for _, label in test]
    y_pred = [model.classify(text) for text, _ in test]

    res = metrics(y_true, y_pred)
    report(counts, test, y_pred, res)

    print()
    print(f"График сохранён: {plot_confusion(res)}")


if __name__ == "__main__":
    main()
