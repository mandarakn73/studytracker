import streamlit as st
import pandas as pd
import os

FILE_NAME = "study_log.csv"

st.set_page_config(page_title="📚 Study Tracker", layout="centered")

st.title("📚 Study Tracker App")
st.markdown("Track your daily study hours easily!")

# Initialize CSV if not present
if not os.path.exists(FILE_NAME):
    df_init = pd.DataFrame(columns=["Subject", "Date", "Hours"])
    df_init.to_csv(FILE_NAME, index=False)

# Form to add new record
with st.form("add_study_form"):
    subject = st.text_input("Subject")
    date = st.date_input("Date")
    hours = st.number_input("Hours Studied", min_value=0.0, step=0.5)

    submitted = st.form_submit_button("Add Record")
    if submitted:
        if subject.strip() == "":
            st.error("Subject cannot be empty.")
        else:
            new_data = pd.DataFrame([[subject, date.strftime("%d-%m-%Y"), hours]],
                                    columns=["Subject", "Date", "Hours"])
            new_data.to_csv(FILE_NAME, mode='a', header=False, index=False)
            st.success("✅ Study record added!")

# Show study records
st.subheader("📄 Study Log")
df = pd.read_csv(FILE_NAME)

if df.empty:
    st.info("No records found yet.")
else:
    st.dataframe(df)

    # Optional: Show total study hours
    total_hours = df["Hours"].sum()
    st.markdown(f"**🕒 Total Hours Studied: {total_hours:.2f} hrs**")
