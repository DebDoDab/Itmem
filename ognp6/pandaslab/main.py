import matplotlib
import pandas
import plotly.express as px


def read_data() -> pandas.DataFrame:
    dataset = pandas.read_csv("Aids2.csv")
    dataset = dataset.query('age != "---------"')
    return dataset


def print_info(dataset: pandas.DataFrame) -> None:
    print("dtypes:\n", dataset.dtypes, "\n")
    print("size:\n", dataset.size, "\n")
    print("shape:\n", dataset.shape, "\n")


def print_sex_info(dataset: pandas.DataFrame) -> None:
    male_aids = dataset.loc[dataset['sex'] == 'M']
    female_aids = dataset.loc[dataset['sex'] == 'F']
    print(f"Male cases percentage: {male_aids.shape[0] / dataset.shape[0]}")
    print(f"Female cases percentage: {female_aids.shape[0] / dataset.shape[0]}")
    print()


def print_alive_men_under_45_percentage(dataset: pandas.DataFrame) -> None:
    male_aids = dataset.query('sex == "M"')
    alive_male_aids_under_45 = male_aids.query('status == "A" and age < 45')
    print(f"Alive men under 45 / Male cases: "
          f"{alive_male_aids_under_45.shape[0] / male_aids.shape[0]}\n")


def plot_above_14(dataset: pandas.DataFrame) -> None:
    above_14_aids = dataset.loc[dataset['age'] > 14, ['age', 'status']]
    max_age = above_14_aids['age'].max()

    dead_percentage = []
    for age in range(15, max_age + 1):
        age_aids_cnt = len(above_14_aids.query('age == @age'))
        if age_aids_cnt == 0:
            dead_percentage.append(0)
            continue
        dead_percentage.append(len(above_14_aids.query(
            'status == "D" and age == @age'
        )) / age_aids_cnt * 100)

    temp_dataset = pandas.DataFrame({
        'percentage': dead_percentage, 'age': range(15, max_age + 1)
    })
    graph = temp_dataset.plot.line(x='age', y='percentage')
    matplotlib.pyplot.show()

    fig = px.line(temp_dataset, x="age", y="percentage", title="Death %")
    fig.show()


def dead_before_30(dataset: pandas.DataFrame) -> None:
    ds = dataset.query('age < 30')
    states = ds['state'].unique()

    dead_percentage = {}
    dead_people_percentage = 0
    for state in states:
        dead_percentage[state] = len(
            ds.query('state == @state and status == "D"')
        ) / ds.query('state == @state').shape[0] * 100
        dead_people_percentage += dead_percentage[state]

    temp_dataset = pandas.DataFrame({
        'percentage': dead_percentage.values(), 'state': dead_percentage.keys()
    })
    plot = temp_dataset.plot.pie(y="percentage", labels=dead_percentage.keys())
    matplotlib.pyplot.show()

    _, ax1 = matplotlib.pyplot.subplots()
    ax1.pie(temp_dataset["percentage"], labels=dead_percentage.keys(),
            autopct=lambda x: str(x * dead_people_percentage / 100) + "%")
    ax1.axis('equal')

    matplotlib.pyplot.show()


def average_age(dataset: pandas.DataFrame) -> None:
    states = dataset['state'].unique()
    avg_age = [{
        'state': 'Australia',
        'average age': dataset['age'].astype("int").mean()
    }]
    for state in states:
        avg_age.append({
            'state': state,
            'average age': dataset.query(
                'state == @state')['age'].astype("int").mean()
        })
    avg_age = pandas.DataFrame(avg_age)
    avg_age.plot.bar(x="state", y="average age")
    matplotlib.pyplot.show()


def state_info(dataset: pandas.DataFrame) -> None:
    states = dataset['state'].unique()
    for state in states:
        print(f"{state=}")
        ds = dataset.query('state == @state')
        min_age = ds['age'].min()
        max_age = ds['age'].max()
        print(f"\t{min_age=}\n\t{max_age=}")
        state_aids = {
            'old': ds.query('age >= 55').shape[0],
            'mid': ds.query('age > 30 and age < 55').shape[0],
            'youth': ds.query('age <= 30').shape[0],
        }
        print(f"\tMost infected part is {max(state_aids, key=state_aids.get)}")


def state_category(dataset: pandas.DataFrame) -> None:
    states = dataset['state'].unique()
    categories = dataset['T.categ'].unique()

    category_cases = []
    for state in states:
        for category in categories:
            category_cases.append({
                'state': state,
                'category': category,
                'total': dataset.loc[dataset["T.categ"] == category].query(
                    'state == @state').shape[0]
            })

    category_cases = pandas.DataFrame(category_cases)

    category_cases.pivot(
        index='state', columns='category', values='total'
    ).plot(kind='bar', stacked=True)
    matplotlib.pyplot.show()


def groups_analyze(dataset: pandas.DataFrame) -> None:
    groups = {
        'old': dataset.query('age >= 55'),
        'mid': dataset.query('age > 30 and age < 55'),
        'youth': dataset.query('age <= 30'),
    }
    for (group, ds) in groups.items():
        alive = ds.query('status == "A"').shape[0]
        dead = ds.query('status == "D"').shape[0]
        if alive > dead:
            print(f"Group {group} has alive > dead")


if __name__ == "__main__":
    dataset = read_data()
    print_info(dataset)
    print_sex_info(dataset)
    print_alive_men_under_45_percentage(dataset)
    plot_above_14(dataset)
    dead_before_30(dataset)
    average_age(dataset)
    state_info(dataset)
    state_category(dataset)
    groups_analyze(dataset)
    print(dataset)

