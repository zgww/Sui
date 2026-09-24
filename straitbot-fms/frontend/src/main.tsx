import React from 'react'
import ReactDOM from 'react-dom/client'
import { LocaleProvider } from '@douyinfe/semi-ui'
import zh_CN from '@douyinfe/semi-ui/lib/es/locale/source/zh_CN'
import { UserProvider } from './store/user'
import { RobotProvider } from './store/robot'
import App from './App'
import './styles.css'

ReactDOM.createRoot(document.getElementById('app')!).render(
  <React.StrictMode>
    <LocaleProvider locale={zh_CN}>
      <UserProvider>
        <RobotProvider>
          <App />
        </RobotProvider>
      </UserProvider>
    </LocaleProvider>
  </React.StrictMode>
)
