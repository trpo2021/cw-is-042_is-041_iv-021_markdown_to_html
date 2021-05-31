Markdown to HTML converter
============
## Примечание.
Данный документ может быть использован для демонстрации работоспособности. Описание примерной работы программы приведено в wiki.
Поддержка редко используемых правил вроде отделения `<pre><code>` табуляцией - не реализована.

## Реализована поддержка следующих правил Markdown:

* `<hr>`
* `<br>`
* `<h1> - <h6> (inline)`
* `<h1> - <h2> (underline)`
* `<pre><code>`
* `<ul><li>`
* `<ol><li>`
* `<blockqoute>`
* `<strong>`
* `<em>`
* `<code>`
* `<img>`
* `<a> (auto/default)`
* `<p>`

# Horizontal rule (`<hr>`)
Горизонтальная черта.  
Использование: на новой строке.  
Синтаксис: `_`|`*` в количестве > 2. Допускается использование пробелов или табуляций.

Пример:
___________

# Break line rule (`<br>`)
Сбросить строку.  
Необходимо поставить 2 или больше пробелов перед переходом на новую строку.

Пример:  
Lorem ipsum dolor sit amet,  
consectetur adipiscing elit

# Heading rule (`<h1>` - `<h6>`)
Заголовок.  
Возможно применение в двух случаях.  
1. Использован символ `#` от 1 до 6 раз подряд и после них что-то есть. Этот подход можно применять в списках, цитатах и т.д.  
Для одной строки доступно только одно применение.
2. Поставить на новой строке 2 или больше `=` для `<h1>` и `-` для `<h2>` соотвественно. Не работает для параграфа.


Пример inline:  
# I'm inline header level 1
## I'm inline header level 2
### I'm inline header level 3
#### I'm inline header level 4
##### I'm inline header level 5
###### I'm inline header level 6
####### I'm not header

Пример underline:  

I'm underline header level 1
==
I'm underline header level 2
--

# Code block rule (`<pre><code>`)
Блок кода.  
Использование: на новой строке.  
Синтаксис: ` в количестве > 3. Для закрытия использование аналогично.

Пример:
```
#include <stdio.h>

int main(void) {
    char *s = "abc";
    printf("%s\n", s);
    return 0;
}
```

# Unordered list (`<ul><li>`)
Ненумерованный список.  
Использование: в начале строки. 4 пробела или 1 табуляция может выделять следующий уровень.  
Синтаксис: `*`|`+`|`-` перед текстом. В список также могут входить цитаты или заголовки.

Пример:
* list item level 0
    + list item level 1
        - list item level 2
    * list item level 1
+ list item level 0

* # header in list
    + > blockquote in list
        + > # blockquote and header in list

# Ordered list (`<ol><li>`)
Нумерованный список.  
Использование: в начале строки. 4 пробела или 1 табуляция может выделять следующий уровень.  
Синтаксис: `число.` перед текстом. В список также могут входить цитаты или заголовки.

Пример:
1. list item level 0
    1. list item level 1
        1. list item level 2
    1. list item level 1
2. list item level 0


# Blockqoute (`<blockqoute>`)
Цитата.  
Использование: в начале строки, либо в списке. Цитаты могут быть вложенными.  
Синтаксис: `> `. В цитате может быть заголовок. Поддержка списков не реализована.

Пример:
> Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
> > Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
> Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.

# Bold (`<strong>`)
Жирный текст.  
Использование: в любом месте документа.  
Синтаксис: символами `*`|`_` с обеих сторон в любом порядке или сочетании в количестве 2. Может включать в себя другие теги.

Пример:  
I'm **bold** text!

# Italic (`<em>`)
Курсивный текст.  
Использование: в любом месте документа.  
Синтаксис: символами `*`|`_` с обеих сторон в любом порядке или сочетании в количестве 1. Может включать в себя другие теги.

Пример:  
I'm *italic* text!

Пример комбинации:  
**bold** и *italic* -> ***bold italic***

# Code (`<code>`)
Строка кода.  
Использование: в любом месте документа.  
Синтаксис: символ \` с обеих сторон в количестве 1. Чтобы в код поместить N-ое количество символов \` достаточно обрамлять N+1.

Пример: 
``some ` code`` обрамляется 2-мя `.

# Image (`<img>`)
Картинка.  
Использование: в любом месте документа.  
Синтаксис: `![...](...)`. В квадратных скобках альтернативный текст, в круглых ссылка на картинку/путь к ней.

Пример:   
![alt text](http://nikulux.ru/wp-content/uploads/2017/09/git_logo.png)

# Link (`<a>`)
Ссылка.  
Использование: в любом месте документа.  
Синтаксис: `[...](...)`. В квадратных скобках альтернативный текст, в круглых ссылка.  
Title не реализован. Форматирование не реализовано.

Пример:  
[our repo](https://github.com/trpo2021/cw-is-042_is-041_iv-021_markdown_to_html)   
[local path](/about/index.html)

# Autolink (`<a>`)
Ссылка.  
Использование: в любом месте документа.  
Синтаксис: `<...>`. В скобках ссылка. Валидация email/url предусмотрена, но требует доработки.

Пример:

<example@gmail.com> - email

<www.youtube.com> - валидная ссылка

<qwerty> - уже не ссылка

# Paragraphs (`<p>`)
Параграф текста.  
Используется неявно. Групирует текст.  
Может быть сброшен некоторыми правилами: `<hr>`|`<br>` на новой строке.

Пример:  
"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

"Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?"
