import ctypes
import os
import sys
from typing import List, Optional, Callable, Any


class List:
    """
    Python класс-обёртка для C-библиотеки со связным списком.
    Реализует ООП-интерфейс поверх C-функций.
    """

    def __init__(self, destroy_func: Optional[Callable] = None, print_func: Optional[Callable] = None):
        """
        Создание нового списка.

        Args:
            destroy_func: Функция для освобождения данных (опционально)
            print_func: Функция для печати данных (опционально)
        """
        lib_path = self._find_library()
        self._lib = ctypes.CDLL(lib_path)
        self._setup_function_types()
        self._list_ptr = self._lib.list_create()
        self._destroy_func = destroy_func
        self._print_func = print_func
        if destroy_func:
            self._setup_destroy_callback()
        if print_func:
            self._setup_print_callback()

    def _find_library(self) -> str:
        """Находит путь к скомпилированной библиотеке."""
        if os.name == 'nt':
            possible_paths = [
                "./liblist.dll",
                "../liblist.dll",
                os.path.join(os.path.dirname(__file__), "..", "liblist.dll"),
                os.path.join(os.path.dirname(__file__), "liblist.dll"),
            ]
        else:
            possible_paths = [
                "./liblist.so",
                "../liblist.so",
                os.path.join(os.path.dirname(__file__), "..", "liblist.so"),
                os.path.join(os.path.dirname(__file__), "liblist.so"),
            ]

        for path in possible_paths:
            if os.path.exists(path):
                return os.path.abspath(path)

        raise FileNotFoundError(
            "Библиотека liblist.so не найдена. "
            "Скомпилируйте её с помощью: gcc -shared -fPIC list.c -o liblist.so"
        )

    def _setup_function_types(self):
        """Настраивает типы аргументов и возвращаемые значения для C-функций."""
        lib = self._lib

        lib.list_create.argtypes = []
        lib.list_create.restype = ctypes.c_void_p

        lib.list_destroy.argtypes = [ctypes.c_void_p]
        lib.list_destroy.restype = None

        lib.list_push_front.argtypes = [ctypes.c_void_p, ctypes.c_int]
        lib.list_push_front.restype = ctypes.c_bool

        lib.list_push_back.argtypes = [ctypes.c_void_p, ctypes.c_int]
        lib.list_push_back.restype = ctypes.c_bool

        lib.list_pop_front.argtypes = [
            ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
        lib.list_pop_front.restype = ctypes.c_bool

        lib.list_pop_back.argtypes = [
            ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
        lib.list_pop_back.restype = ctypes.c_bool

        lib.list_size.argtypes = [ctypes.c_void_p]
        lib.list_size.restype = ctypes.c_size_t

        lib.list_is_empty.argtypes = [ctypes.c_void_p]
        lib.list_is_empty.restype = ctypes.c_bool

        lib.list_clear.argtypes = [ctypes.c_void_p]
        lib.list_clear.restype = None

        lib.list_at.argtypes = [ctypes.c_void_p, ctypes.c_size_t]
        lib.list_at.restype = ctypes.POINTER(ctypes.c_int)

        lib.list_find.argtypes = [ctypes.c_void_p, ctypes.c_int]
        lib.list_find.restype = ctypes.c_int

        lib.list_insert_at.argtypes = [
            ctypes.c_void_p, ctypes.c_size_t, ctypes.c_int]
        lib.list_insert_at.restype = ctypes.c_bool

        lib.list_remove_at.argtypes = [
            ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_int)]
        lib.list_remove_at.restype = ctypes.c_bool

        lib.list_sort.argtypes = [ctypes.c_void_p]
        lib.list_sort.restype = None

        lib.list_print.argtypes = [ctypes.c_void_p]
        lib.list_print.restype = None

    def _setup_destroy_callback(self):
        """Настраивает callback для уничтожения данных."""
        if not self._destroy_func:
            return

        DESTROY_FUNC = ctypes.CFUNCTYPE(None, ctypes.c_int)

        @DESTROY_FUNC
        def destroy_callback(value):
            self._destroy_func(value)

        self._destroy_callback = destroy_callback

        if hasattr(self._lib, 'list_set_destroy_func'):
            self._lib.list_set_destroy_func.argtypes = [
                ctypes.c_void_p, DESTROY_FUNC]
            self._lib.list_set_destroy_func.restype = None
            self._lib.list_set_destroy_func(self._list_ptr, destroy_callback)

    def _setup_print_callback(self):
        """Настраивает callback для печати данных."""
        if not self._print_func:
            return

        PRINT_FUNC = ctypes.CFUNCTYPE(None, ctypes.c_int)

        @PRINT_FUNC
        def print_callback(value):
            self._print_func(value)

        self._print_callback = print_callback

        if hasattr(self._lib, 'list_set_print_func'):
            self._lib.list_set_print_func.argtypes = [
                ctypes.c_void_p, PRINT_FUNC]
            self._lib.list_set_print_func.restype = None
            self._lib.list_set_print_func(self._list_ptr, print_callback)

    def __del__(self):
        """Деструктор - освобождает C-ресурсы."""
        if hasattr(self, '_list_ptr') and self._list_ptr:
            self._lib.list_destroy(self._list_ptr)

    def __len__(self) -> int:
        """Возвращает размер списка."""
        return self._lib.list_size(self._list_ptr)

    def __bool__(self) -> bool:
        """Проверяет, не пуст ли список."""
        return not self._lib.list_is_empty(self._list_ptr)

    def __getitem__(self, index: int) -> int:
        """Получение элемента по индексу."""
        if isinstance(index, slice):
            result = []
            start, stop, step = index.indices(len(self))
            for i in range(start, stop, step):
                val = self._lib.list_at(self._list_ptr, i)
                if val:
                    result.append(val.contents.value)
                else:
                    raise IndexError("list index out of range")
            return result
        else:
            if index < 0:
                index = len(self) + index
            val_ptr = self._lib.list_at(self._list_ptr, index)
            if not val_ptr:
                raise IndexError("list index out of range")
            return val_ptr.contents.value

    def __setitem__(self, index: int, value: int):
        """Установка элемента по индексу."""
        if index < 0:
            index = len(self) + index

        val_ptr = self._lib.list_at(self._list_ptr, index)
        if not val_ptr:
            raise IndexError("list index out of range")

        out_val = ctypes.c_int()
        if self._lib.list_remove_at(self._list_ptr, index, ctypes.byref(out_val)):
            self._lib.list_insert_at(self._list_ptr, index, value)

    def __iter__(self):
        """Итератор по элементам списка."""
        self._iter_index = 0
        return self

    def __next__(self) -> int:
        """Следующий элемент итератора."""
        if self._iter_index >= len(self):
            raise StopIteration
        val = self[self._iter_index]
        self._iter_index += 1
        return val

    def __contains__(self, value: int) -> bool:
        """Проверка наличия элемента в списке."""
        return self._lib.list_find(self._list_ptr, value) != -1

    def __repr__(self) -> str:
        """Строковое представление списка."""
        elements = [str(self[i]) for i in range(len(self))]
        return f"List([{', '.join(elements)}])"

    def __str__(self) -> str:
        """Строковое представление для пользователя."""
        return f"[{', '.join(str(self[i]) for i in range(len(self)))}]"

    def push_front(self, value: int) -> bool:
        """Добавляет элемент в начало списка."""
        return self._lib.list_push_front(self._list_ptr, value)

    def push_back(self, value: int) -> bool:
        """Добавляет элемент в конец списка."""
        return self._lib.list_push_back(self._list_ptr, value)

    def pop_front(self) -> Optional[int]:
        """Удаляет и возвращает элемент из начала списка."""
        out_val = ctypes.c_int()
        if self._lib.list_pop_front(self._list_ptr, ctypes.byref(out_val)):
            return out_val.value
        return None

    def pop_back(self) -> Optional[int]:
        """Удаляет и возвращает элемент из конца списка."""
        out_val = ctypes.c_int()
        if self._lib.list_pop_back(self._list_ptr, ctypes.byref(out_val)):
            return out_val.value
        return None

    def front(self) -> Optional[int]:
        """Возвращает первый элемент списка без удаления."""
        val_ptr = self._lib.list_at(self._list_ptr, 0)
        return val_ptr.contents.value if val_ptr else None

    def back(self) -> Optional[int]:
        """Возвращает последний элемент списка без удаления."""
        val_ptr = self._lib.list_at(
            self._list_ptr, len(self) - 1 if len(self) > 0 else 0)
        return val_ptr.contents.value if val_ptr and len(self) > 0 else None

    def clear(self):
        """Очищает список."""
        self._lib.list_clear(self._list_ptr)

    def insert(self, index: int, value: int) -> bool:
        """Вставляет элемент по индексу."""
        if index < 0:
            index = len(self) + index
        return self._lib.list_insert_at(self._list_ptr, max(0, index), value)

    def remove(self, value: int) -> bool:
        """Удаляет первое вхождение значения."""
        index = self._lib.list_find(self._list_ptr, value)
        if index != -1:
            out_val = ctypes.c_int()
            return self._lib.list_remove_at(self._list_ptr, index, ctypes.byref(out_val))
        return False

    def pop(self, index: int = -1) -> Optional[int]:
        """Удаляет и возвращает элемент по индексу."""
        if index < 0:
            index = len(self) + index

        out_val = ctypes.c_int()
        if self._lib.list_remove_at(self._list_ptr, index, ctypes.byref(out_val)):
            return out_val.value
        return None

    def index(self, value: int) -> int:
        """Возвращает индекс первого вхождения значения."""
        return self._lib.list_find(self._list_ptr, value)

    def sort(self):
        """Сортирует список."""
        self._lib.list_sort(self._list_ptr)

    def to_list(self) -> List[int]:
        """Преобразует в стандартный список Python."""
        return [self[i] for i in range(len(self))]

    def print(self):
        """Печатает список с использованием C-функции."""
        self._lib.list_print(self._list_ptr)