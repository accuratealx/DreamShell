## Добавление собственной команды

### Последовательность действий

1. Подготовить cpp с зависимостью __DreamServerShell__
2. Создать класс новой команды унаследовавшись от __TDreamServerShellCommand__
3. В конструкторе команды определить параметры
4. В методе __TStringArray Help()__ поправить помощь
5. Написать реализацию в методе __verride TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)__
6. Создать класс модификатор __modded class TDreamServerShellCommandList__
7. Переопределить метод __override void RegisterCommands()__
8. Зарегистрировать команду
9. Запаковать pbo
10. Серверная часть готова