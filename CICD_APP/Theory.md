# Headless‑first, Task‑Oriented, CI/CD‑ready, UI‑optional

## 1. Tổng quan toàn bộ hệ thống

```mermaid
flowchart TB
    Entry["Entry Point<br/>(CLI / Batch / UI)"]

    subgraph Adapters["Adapters Layer"]
        CLI["CLI Adapter"]
        
        subgraph UI_Adapter["UI Adapter - Chạy trên UI/Main Thread"]
            direction TB
            subgraph InputLayer["Input Layer"]
                InputParser["Input Parser"]
                InputBoundary["Input Boundary"]
            end
            subgraph DisplayLayer["Display Layer"]
                DisplayBoundary["Display Boundary"]
                ViewModel["ViewModel / DTO"]
                DisplayFormatter["Display Formatter"]
            end
            View["View<br/>(QMainWindow, Widgets)"]
            Presenter["Presenter"]
        end
        
    end

    subgraph Core["Application Core (Headless-first)"]
        AppController["AppController<br/>(Điều phối request đồng bộ)"]
        ApplicationService["ApplicationService<br/>(Use Cases / Business Logic)"]
    end

    subgraph Domain["Domain Layer"]
        DomainModel["Domain Model<br/>(Entities, Value Objects)"]
        DomainEvent["Domain Events<br/>(StudentAdded, GradeUpdated...)"]
    end

    subgraph Infra["Infrastructure"]
        Repository["Repository<br/>(Data Access)"]
        DB[("(Database)")]
    end

    %% ===== 1. Luồng khởi tạo =====
    Entry --> CLI
    Entry --> View

    %% ===== 2. Luồng điều khiển (Control Flow) =====
    View -- "1. Người dùng thao tác" --> InputParser
    InputParser -- "2. Dữ liệu đã chuẩn hóa" --> InputBoundary
    InputBoundary -- "3. Gọi Presenter" --> Presenter
    
    Presenter -- "4. Gửi lệnh (Command/Request)" --> AppController
    AppController -- "5. Gọi Use Case tương ứng" --> ApplicationService

    ApplicationService -- "6. Thao tác Domain" --> DomainModel
    DomainModel -- "7. Tạo sự kiện" --> DomainEvent
    DomainEvent -- "8. Trả về ApplicationService" --> ApplicationService

    ApplicationService -- "9. Lưu/Xuất dữ liệu" --> Repository
    Repository -- "10. Kết nối" --> DB


    %% ===== 4. Luồng hiển thị (Display Flow) =====
    Presenter -- "14. Gửi kết quả hiển thị" --> DisplayBoundary
    DisplayBoundary -- "15. Dữ liệu thô" --> DisplayFormatter
    DisplayFormatter -- "16. Tạo ViewModel" --> ViewModel
    ViewModel -- "17. Cập nhật View" --> View
```

- UI KHÔNG thuộc Core
- Core chạy được không cần UI
- CI/CD chạy qua CLI / Batch

## 2. Chi tiết Task System

```mermaid
flowchart LR
    TaskType --> TaskDefinition
    TaskDefinition --> TaskFactory
    TaskFactory --> DomainTask
    DomainTask --> TaskAdapter
    TaskAdapter --> TaskExecutor
    TaskExecutor --> TaskRuntimeStore
```

- TaskDefinition: metadata + wiring
- DomainTask: logic thực sự
- TaskAdapter: bridge Qt / thread
- TaskRuntimeStore: state tập trung

## 3. TaskRuntimeStore – Single Source of Truth

```mermaid
flowchart TB
    Worker["Worker Thread<br/>(Task)"]
    Store["TaskRuntimeStore<br/>(Common Data)"]
    Presenter
    UI

    Worker -->|update state| Store
    Store -->|signal / notify| Presenter
    Presenter --> UI
```

## 4. Domain Event → Task

```mermaid
sequenceDiagram
    participant Domain
    participant App as ApplicationService
    participant Registry as TaskRegistry
    participant Executor
    participant Store as TaskRuntimeStore

    Domain->>Domain: business action
    Domain->>App: DomainEvent
    App->>Registry: select task type
    Registry->>Executor: create & submit task
    Executor->>Store: update runtime state
```

- Domain KHÔNG trigger task
- Application quyết định phản ứng

## 5. Event Bus + Signal/Slot (MVP‑safe)

```mermaid
flowchart TB
    Store["TaskRuntimeStore"]
    Bus["EventBus<br/>(Qt signal/slot)"]

    Presenter
    View
    Logger

    Store -->|emit state-event| Bus
    Bus --> Presenter
    Presenter --> View
    Bus --> Logger
```

- Presenter nghe state event
- View chỉ update qua Presenter
- Không phá MVP

## 6. Thread model

```mermaid
flowchart TB
    subgraph Process["Single OS Process"]
        UIThread["UI Thread<br/>(Main Thread)"]

        subgraph Workers["Worker Threads"]
            T1[Task A]
            T2[Task B]
            T3[DB / IO]
        end
    end

    UIThread -. observe .-> Workers
```

- UI = 1 thread duy nhất
- Task = multiple worker threads
- CLI mode = không có UI thread

## 7. Chạy full app bằng CLI / Batch (CI/CD)

```mermaid
sequenceDiagram
    participant CI
    participant CLI
    participant Core
    participant Task
    participant Store
    participant Repo

    CI->>CLI: app --batch
    CLI->>Core: start use case
    Core->>Task: submit task
    Task->>Store: update progress
    Store->>Repo: persist
    Repo-->>CI: final state
```

- Không UI
- Không human interaction
- CI chạy full flow

## 8. UI chỉ là Adapter

```mermaid
flowchart LR
    UI --> Presenter
    Presenter --> ApplicationService
    ApplicationService --> TaskRuntimeStore
    TaskRuntimeStore --> Presenter
```

## 9. Toàn bộ flow tóm gọn

```mermaid
flowchart TB
    User
    User -->|CLI / UI| Entry

    Entry --> AppController
    AppController --> ApplicationService
    ApplicationService --> Domain
    Domain --> ApplicationService

    ApplicationService --> TaskSystem
    TaskSystem --> TaskRuntimeStore
    TaskRuntimeStore --> UI
```

## 10. KẾT LUẬN

Một Headless‑First, Task‑Oriented Application, có đặc tính:

- Core chạy độc lập UI
- Task + State là trung tâm
- Domain event → Application decide
- Multi‑thread an toàn
- CI/CD chạy full app
- UI chỉ là adapter
